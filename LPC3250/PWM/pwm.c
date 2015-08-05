#include <linux/kernel.h>       /* We're doing kernel work */
#include <linux/module.h>       /* Specifically, a module */
#include <linux/fs.h>
#include <asm/uaccess.h>       /* for get_user and put_user */
#include <mach/hardware.h>
#include "pwm.h"

uint32_t pwm1_addr = 0x4005C000;
uint32_t pwm2_addr = 0x4005C004;
uint32_t pwm_clock_addr = 0x400040B8;
uint32_t pwm_lcd = 0x40004054;
/* 
 * The message the device will give when asked 
 */
static char Message[BUF_LEN];

/* 
 * How far did the process reading the message get?
 * Useful if the message is larger than the size of the
 * buffer we get to fill in device_read. 
 */
static char *Message_Ptr;
static int Device_Open = 0;

bool toggle_pwm(uint32_t val, uint32_t *addr, uint32_t pwm_nr)
{
  bool returner = false;
  if(val <= 1)
  {
    uint32_t *pwm_clock = io_p2v(pwm_clock_addr); 
    uint32_t *pwm_lcd_set = io_p2v(pwm_lcd);
    //make sure the lcd doesn't block the pwm
    *pwm_lcd_set &= 0xFFFFFF3F;

    //toggle pwm_block_enable
    if (pwm_nr == 1){
      *pwm_clock &= ~0x01;
      *pwm_clock |= val;
    }
    else if (pwm_nr == 2)
    {
      *pwm_clock &= ~0x04;
      *pwm_clock |= val << 2;
    }

    //toggle pwmX_enable
    *addr &= ~(0x80000000);
    *addr |= (val << 31);
    returner = true;
  }
  return returner;
}

/* 
 * The function to calculate + write the values for the frequency
 * it will first check what the clock frequency should be
 * Then it will check the divider, and finally the reload value for the PWM
 * after that, it will write the correct values into the registers
 */
bool calculate_and_write_pwm_frequency(uint32_t frequency_in_hz, uint32_t *addr, uint32_t pwm_nr)
{
  bool returner = false;
  if (frequency_in_hz >= 1 || frequency_in_hz <= 50000)
  {
    uint32_t temp;
    uint32_t clock_freq_divided;
    uint32_t divider;
    uint32_t reload_val;
    uint32_t *pwm_clock = io_p2v(pwm_clock_addr);
    uint32_t clock_freq = 13000000;

    if (frequency_in_hz <= 15) {
      clock_freq = 32000;
    }
    temp = frequency_in_hz * 256; 
    divider = 1;
    while ((clock_freq / divider) / temp > 256) {
      divider++;
    }

    clock_freq_divided = clock_freq / divider;
    reload_val = clock_freq_divided / temp;

    //calculation done, now we need to set the PWM_CLOCK source & frequency
    if (pwm_nr == 1){
      //set clock source selection, 0 = PERIPH_CLK, 1 = 32kHz RTC_CLK
      if (clock_freq == 13000000) {
        *pwm_clock |= 0x02;
      }
      else {
        *pwm_clock &= ~ 0x02;
      }
      //set the clock divider, first "reset" it, then fill in the right value
      *pwm_clock &= ~0xF0;
      *pwm_clock |= divider << 4;
    }
    else if (pwm_nr == 2) {
      //set clock source selection, 0 = PERIPH_CLK, 1 = 32kHz RTC_CLK
      if (clock_freq == 13000000) {
        *pwm_clock |= 0x08;
      }
      else {
        *pwm_clock &= ~ 0x08;
      }

      //set the clock divider, first "reset" it, then fill in the right value
      *pwm_clock &= ~0xF00;
      *pwm_clock |= divider << 8;
    }
    //set the reload value of the correct PWM
    *addr &= ~0xFF00;
    *addr |= reload_val << 8;
    returner = true;
  }
  return returner;
}

/* 
 * function to set the PWM duty.
 */
bool set_pwm_duty(uint32_t val, uint32_t *addr)
{
  bool returner = false;
  if(val <= 255)
  {
    *addr &= ~0xFF;
    *addr |= val;
    returner = true;
  }
  return returner;
}

/* 
 * This function will read the values that have been written to the registers
 * that set the frequency, after reading those, it will calculate the frequency and return the value.
 */
uint32_t read_pwm_frequency(uint32_t *addr, uint32_t pwm_nr)
{
  uint32_t returner = 0;
  uint32_t *pwm_clock = io_p2v(pwm_clock_addr);
  uint32_t pwm_frequency = 0;
  volatile uint32_t pwm_reload;
  uint32_t pwm_clock_source = 0;
  uint32_t pwm_clock_divider = 0;
  uint8_t pwm_choice;

  pwm_reload = *addr;
  pwm_reload  &= 0xFF00;
  pwm_reload >>= 8;
  if(pwm_reload > 0) {
    if (pwm_nr == 1) {
      pwm_clock_divider = (*pwm_clock & 0xF0) >> 4;
      pwm_clock_source = (*pwm_clock & 0x02) >> 1;
      pwm_choice = 1; 
    } 
    else {
      pwm_clock_divider = (*pwm_clock & 0xF00) >> 8;
      pwm_clock_source = (*pwm_clock & 0x08) >> 3;
      pwm_choice = 2; 
    }
    pwm_frequency = 32000;
    if(pwm_clock_source) {
      pwm_frequency = 13000000;
    }
    pwm_frequency = pwm_frequency/pwm_clock_divider;
    returner = (pwm_frequency/pwm_reload) / 256;
  }
  return returner;
}



/* 
 * This is called whenever a process attempts to open the device file 
 */
static int device_open(struct inode *inode, struct file *file) {
  uint32_t minornumber = inode->i_rdev & 0xFF;
  file->private_data = minornumber;// set private data of the struct
  
  if (Device_Open)
    return -EBUSY;

  Device_Open++;
  Message_Ptr = Message;
  try_module_get(THIS_MODULE);

  return SUCCESS;
}

static int device_release(struct inode *inode, struct file *file) {
  Device_Open--;
  module_put(THIS_MODULE);
  return SUCCESS;
}

/* 
 * This function is called whenever a process which has already opened the
 * device file attempts to read from it.
 */
static ssize_t device_read(struct file *file, char __user * buffer,  size_t length, loff_t * offset) {
  /* 
   * Number of bytes actually written to the buffer 
   */
  int bytes_read = 0;
  uint32_t register_val;
  uint32_t value = 0;
  uint32_t *pwm_addres;
  uint32_t minornumber;
  minornumber = (uint32_t)file->private_data;

  //the io_p2v gets cast to an uint32_t, this because the compiler will give warnings about not casting it.
  if (minornumber < 3){
    register_val = (uint32_t)io_p2v(pwm1_addr); 
  }
  else{
    register_val = (uint32_t)io_p2v(pwm2_addr);
  }

  //sprintf() is used to print the message to the console.
  pwm_addres = &register_val;
  switch(minornumber) {
    case 0: //pwm1_enable
      value = (*pwm_addres & 0x80000000) >> 31;
      sprintf(Message, "PWM1: value for enable: %u\n", value);
      break;
    case 1: //pwm1_frequency
      value = read_pwm_frequency(pwm_addres, 1);
      sprintf(Message, "PWM1: value for frequency %u\n", value);
      break;
    case 2: //pwm1_duty
      value = (*pwm_addres & 0xFF);
      sprintf(Message, "PWM1: value for duty: %u\n", value);
      break;
    case 3: //pwm2_enable
      value = (*pwm_addres & 0x80000000) >> 31;
      sprintf(Message, "PWM2: value for enable: %u\n", value);
      break;
    case 4: //pwm2_freq
      value = read_pwm_frequency(pwm_addres, 2);
      sprintf(Message, "PWM2: value for frequency %u\n", value);
      break;
    case 5: //pwm2_duty
      value = (*pwm_addres & 0xFF);
      sprintf(Message, "PWM2: value for duty: %u\n", value);
      break;
  }


  /* 
   * If we're at the end of the message, return 0
   * (which signifies end of file) 
   */
  if (*Message_Ptr == 0)
    return 0;

  /* 
   * Actually put the data into the buffer 
   */
  while (length && *Message_Ptr) {

    /* 
     * Because the buffer is in the user data segment,
     * not the kernel data segment, assignment wouldn't
     * work. Instead, we have to use put_user which
     * copies data from the kernel data segment to the
     * user data segment. 
     */
    put_user(*(Message_Ptr++), buffer++);
    length--;
    bytes_read++;
  }

  printk(KERN_INFO "Read %d bytes, %d left\n", bytes_read, length);

  /* 
   * Read functions are supposed to return the number
   * of bytes actually inserted into the buffer 
   */
  return bytes_read;
}

/* 
 * This function is called when somebody tries to
 * write into our device file. 
 */
static ssize_t device_write(struct file *file, const char __user * buffer, size_t length, loff_t * offset) {
  int i;
  uint32_t new_value = 0;
  uint32_t register_val;
  uint32_t *pwm_addres;
  uint32_t minornumber = 0;

  for (i = 0; i < length && i < BUF_LEN; i++) {
    get_user(Message[i], buffer + i);
  }

  Message_Ptr = Message;

  sscanf (buffer, "%u", &new_value);
  minornumber = (uint32_t)file->private_data;

  //check for what PWM it is, if the minor nr. is below 4, it' s pwm1
  if (minornumber < 3){
    register_val = (uint32_t)io_p2v(pwm1_addr);
  }
  else{
    register_val = (uint32_t)io_p2v(pwm2_addr); 
  }
  pwm_addres = &register_val;

  //during this switch/case the printk function is used to print towards the console
  //the sprintf() function wouldn' t print it into the console.
  switch(minornumber) {
    case 0: //pwm1_enable
      if (!toggle_pwm(new_value, pwm_addres, 1)) {
        printk("Failed to toggle PWM1!\n");
      }
      break;
    case 1: //pwm1_freq
      if(!calculate_and_write_pwm_frequency(new_value, pwm_addres, 1)) {
        printk("Failed to set PWM1 frequency!\n");
      }
      break;
    case 2: //pwm1_duty
      if (!set_pwm_duty(new_value, pwm_addres)) {
        printk("Failed to set PWM1 duty!\n");
      }
      break;
    case 3: //pwm2_enable
      if (!toggle_pwm(new_value, pwm_addres, 2)) {
       printk("Failed to toggle PWM2!\n");
      }
      break;
    case 4: //pwm2_freq
      if (!calculate_and_write_pwm_frequency(new_value, pwm_addres, 2)) {
        printk("Failed to set PWM2 frequency!\n");
      }
      break;
    case 5: //pwm2_duty
      if (!set_pwm_duty(new_value, pwm_addres)) {
        printk("Failed to set PWM2 duty!\n");
      }
      break;
  }
  printk("Device write, value written: %u\n", new_value);

  /* 
   * Again, return the number of input characters used 
   */
  return i;

}


/* Module Declarations */

/* 
 * This structure will hold the functions to be called
 * when a process does something to the device we
 * created. Since a pointer to this structure is kept in
 * the devices table, it can't be local to
 * init_module. NULL is for unimplemented functions. 
 */
struct file_operations Fops = {
  .read = device_read,
  .write = device_write,
  .open = device_open,
  .release = device_release,    /* a.k.a. close */
};

/* 
 * Initialize the module - Register the character device 
 */
int init_module() {
  int ret_val;
  /* 
   * Register the character device (atleast try) 
   */
  ret_val = register_chrdev(MAJOR_NUM, DEVICE_NAME, &Fops);

  /* 
   * Negative values signify an error 
   */
  if (ret_val < 0) {
    printk(KERN_ALERT "%s failed with %d\n",
      "Sorry, registering the character device ", ret_val);
    return ret_val;
  }

  printk(KERN_INFO "%s The major device number is %d.\n",
    "Registeration is a success", MAJOR_NUM);

  return 0;
}

/* 
 * Cleanup - unregister the appropriate file from /proc 
 */
void cleanup_module() {
  /* 
   * Unregister the device 
   */
  unregister_chrdev(MAJOR_NUM, DEVICE_NAME);

}