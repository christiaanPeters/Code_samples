#include <linux/kernel.h>       /* We're doing kernel work */
#include <linux/module.h>       /* Specifically, a module */
#include <linux/fs.h>
#include <asm/uaccess.h>        /* for get_user and put_user */
#include <mach/hardware.h>
#include <linux/kdev_t.h>
#include <linux/slab.h>
#include <linux/kobject.h>   /* Necessary because we use sysfs */
#include <linux/device.h>
#include "GPIO.h"

static char Message[12][MSG_LEN];
static char * MsgPtr[12];

struct pin_info pins[] = {
{"j3_40", P0, 0, 0}, {"j2_24", P0, 1, 1}, {"j2_11", P0, 2, 2},
{"j2_12", P0, 3, 3}, {"j2_13", P0, 4, 4}, {"j2_14", P0, 5, 5},
{"j3_33", P0, 6, 6}, {"j1_27", P0, 7, 7}, {"j3_47", P2, 0, 0},
{"j3_56", P2, 1, 1}, {"j3_48", P2, 2, 2}, {"j3_57", P2, 3, 3},
{"j3_49", P2, 4, 4}, {"j3_58", P2, 5, 5}, {"j3_50", P2, 6, 6},
{"j3_45", P2, 7, 7}, {"j1_49", P2, 8, 8}, {"j1_50", P2, 9, 9},
{"j1_51", P2,10,10}, {"j1_52", P2,11,11}, {"j1_53", P2, 12, 12},
{"j3_54", P3, 10, 25}, {"j3_46", P3, 11, 26}, {"j3_36", P3, 14, 29}, 
{"j1_24", P3, 24, 30}
};
#define GPIO_SIZE (sizeof(pins)/sizeof(pins[0]))
#define HEADER_PIN_SIZE 5
#define COMMAND_SIZE 4
#define ARGUMENT_SIZE 6
#define SAFE_BUFFER_SIZE 15
#define HIGH 1
#define LOW 0
#define ERROR -1
#define ERROR_2 2

#define sysfs_dir  "gpio"
#define sysfs_file "data"

uint32_t read_bit_out_of_address(uint32_t address, uint32_t bit) {
	uint32_t mask = 0;
	uint32_t return_val = 0;
	uint32_t *hw_addres = io_p2v(address);

	mask = 1 << (bit);	
	return_val = hw_addres[0] & mask;
	return_val = return_val >> (bit);
	return return_val;
}

void write_bit_to_address(uint32_t address, uint32_t bit, uint32_t value) {
	uint32_t mask = 0;
	uint32_t *hw_addres = io_p2v(address);

	mask  = value << (bit);	
	hw_addres[0] ^= mask;
}

/*
 * check wether or not you can use the specified pin
 */
bool can_use_gpio(char * header_pin ) {
	bool returner = false;
	int i;

	for(i=0;i<GPIO_SIZE;i++)
	{
		if(strcmp(header_pin, pins[i].header_pin) == 0 )
		{
			returner = true;
		}
	}
	return returner;
}

/* 
 * return the requested pin
 */
struct pin_info get_gpio_info(char * header_pin ) {
	int i;
	struct pin_info temp;

	for(i=0;i<GPIO_SIZE;i++)
	{
		if(strcmp(header_pin, pins[i].header_pin) == 0 )
		{
			temp = pins[i];
		}
	}
	return temp;
}

/* 
 * input returns false, output returns true
 * because false is 0 and true is 1 
 * the register indicates input is 0 and output is 1
 */
bool get_direction(struct pin_info pin) {
	bool returner = false;
	uint32_t pin_state = 0;
	switch(pin.port) {
		case P0:	
			pin_state = read_bit_out_of_address(P0_DIRECTION_STATE, pin.input_bit);
			break;
		case P1:
			pin_state = read_bit_out_of_address(P1_DIRECTION_STATE, pin.input_bit);
			break;
		case P2:
			pin_state = read_bit_out_of_address(P2_3_DIRECTION_STATE, pin.input_bit);
			break;
		case P3: 
			pin_state = read_bit_out_of_address(P2_3_DIRECTION_STATE, pin.output_bit);
			break;
		default:
			printk(KERN_INFO "the software tried to get the settings of the pin, but failed, please try a different pin\n");
			break;
	}
	if(pin_state == HIGH)
	{
		returner = true;
	} 
	return returner;
}

/*
 * because p2 and p3 are shared p3 directory index starts at bit register 25 
 */
bool set_gpio_direction(uint32_t value, struct pin_info pin) {
	bool returner = false;
	switch(pin.port) {
		case P0:
			if(value == HIGH) { 
				write_bit_to_address(P0_DIRECTION_CLR, pin.input_bit, value);
				returner = true;
			} 
			else if( value == LOW)// output set the set register
			{ 
				value=HIGH;
				write_bit_to_address(P0_DIRECTION_SET, pin.input_bit, value);
				returner = true;
			}
			break;
		case P1:
			if(value == HIGH) { 
				write_bit_to_address(P1_DIRECTION_CLR, pin.input_bit, value);
				returner = true;
			} 
			else if( value == LOW)// output set the set register
			{ 
				value=HIGH;
				write_bit_to_address(P1_DIRECTION_SET, pin.input_bit, value);
				returner = true;
			}
			break;
		case P2:
			if(value == HIGH) { 
				write_bit_to_address(P2_3_DIRECTION_CLR, pin.input_bit, value);
				returner = true;
			} 
			else if( value == LOW)// output set the set register
			{ 
				value=HIGH;
				write_bit_to_address(P2_3_DIRECTION_SET, pin.input_bit, value);
				returner = true;
			}
			break;
		case P3: 
			if(value == HIGH) { 
				write_bit_to_address(P2_3_DIRECTION_CLR, pin.output_bit, value);
				returner = true;
			} 
			else if( value == LOW)// output set the set register
			{ 
				value=HIGH;
				write_bit_to_address(P2_3_DIRECTION_SET, pin.output_bit, value);
				returner = true;
			}
			break;
		default:
			printk(KERN_INFO "action not supported\n");
			break;
	}
	return returner;
}

int16_t read_input_pin_value(struct pin_info pin) {
	int16_t pin_state = -1;
	if(get_direction(pin) == INPUT) // see get_directon header comment
	{
		switch(pin.port) {
			case P0:	
				pin_state = read_bit_out_of_address(P0_INPUT_STATE, pin.input_bit);
				break;
			case P1:
				pin_state = read_bit_out_of_address(P1_INPUT_STATE, pin.input_bit);
				break;
			case P2:
				pin_state = read_bit_out_of_address(P2_INPUT_STATE, pin.input_bit);
				break;
			case P3: 
				pin_state = read_bit_out_of_address(P3_INPUT_STATE, pin.input_bit);
				break;
			default:
				printk(KERN_INFO "this operation is not supported\n");
				break;
		}
	}
	else
	{
		printk(KERN_INFO "you tried to read a pin which is not configured as input\n");
	}
	return pin_state;
}

/*
 * when value is 0 it indicates that it needs to clear output to low state.
 * this can only be done by writing a 1 to the correct clear register.
 * after the pin has been set to low, the system automatically sets the 1 in the clear register back to 0.
 */
bool write_output_pin_value(struct pin_info pin, uint32_t value) {
	bool returner = false;
	if(get_direction(pin) == OUTPUT) // see get_directon header comment
	{
		switch(pin.port) {
			case P0:
				if(value ==HIGH) {	
					write_bit_to_address(P0_OUTPUT_SET, pin.output_bit, value);
					returner = true;
				} 
				else 
				{
					value = HIGH;
					write_bit_to_address(P0_OUTPUT_CLR, pin.output_bit, value);
					returner = true;
				}
				break;
			case P1:
				if(value ==HIGH) {	
					write_bit_to_address(P1_OUTPUT_SET, pin.output_bit, value);
					returner = true;
				} 
				else 
				{
					value = HIGH;
					write_bit_to_address(P1_OUTPUT_CLR, pin.output_bit, value);
					returner = true;
				}
				break;
			case P2:
				if(value ==HIGH) {	
					write_bit_to_address(P2_OUTPUT_SET, pin.output_bit, value);
					returner = true;
				} 
				else 
				{
					value = HIGH;
					write_bit_to_address(P2_OUTPUT_CLR, pin.output_bit, value);
					returner = true;
				}
				break;
			case P3: 
				if(value ==HIGH) {	
					write_bit_to_address(P3_OUTPUT_SET, pin.output_bit, value);
					returner = true;
				} 
				else 
				{
					value = HIGH;
					write_bit_to_address(P3_OUTPUT_CLR, pin.output_bit, value);
					returner = true;
				}
				break;
			default:
				printk(KERN_INFO "this operation is not supported\n");
				break;
		}
	}
	else
	{
		printk(KERN_INFO "direction of the pin is wrong or not set\n");
	}
	return returner;
}

void init_registers(void) {
	int16_t pin_zero;
	int16_t pin_one;
	int16_t pin_two;
	// disable the lcd power
	write_bit_to_address(LCD_CTRL, LCD_POWER_PIN, LOW);
	//P0 set channel right
	for (pin_zero = 0; pin_zero < 8; pin_zero++)
	{
		write_bit_to_address(P0_MUTEX_CLR, pin_zero, HIGH);
	}
	//P1 set channel right
	for (pin_one = 0; pin_one < 24; pin_one++)
	{
		write_bit_to_address(P1_MUTEX_SET, pin_one, HIGH);
	}
	//P2 set channel right
	for (pin_two = 0, pin_two < 6; pin_two++)
	{
		write_bit_to_address(P2_MUTEX_CLR, pin_two, HIGH);
	}
	//P3 set channel right
	write_bit_to_address(P3_MUTEX_CLR, 2, HIGH);
	write_bit_to_address(P3_MUTEX_CLR, 10, HIGH);
	write_bit_to_address(P3_MUTEX_CLR, 12, HIGH);
	write_bit_to_address(P3_MUTEX_CLR, 13, HIGH);
	write_bit_to_address(P3_MUTEX_CLR, 14, HIGH);
	write_bit_to_address(P3_MUTEX_CLR, 15, HIGH);
	write_bit_to_address(P3_MUTEX_CLR, 16, HIGH);
	write_bit_to_address(P3_MUTEX_CLR, 18, HIGH);
}

void print_state(int32_t value) {
	switch(value)
	{
		case ERROR:
		// don't print anything because this is already done in the read_input_pin_value function
		break;
		case LOW:
			printk(KERN_INFO "input\n");
		break;
		case HIGH:
			printk(KERN_INFO "output\n");
		break;
		default:
			printk(KERN_INFO "value isn't what is suspected, try again\n");
		break;
	}
}

void print_value(int32_t value) {
	switch(value)
	{
		case ERROR:
		// don't print anything because this is already done in the read_input_pin_value function
		break;
		case LOW:
			printk(KERN_INFO "low\n");
		break;
		case HIGH:
			printk(KERN_INFO "high\n");
		break;
		default:
			printk(KERN_INFO "value isn't what is suspected, try again\n");
		break;
	}
}

uint32_t convert_argument(char* arg) {
	int16_t returner = ERROR_2;
	if(strcmp(arg,"input")==0) {
		returner = HIGH;
	}
	else if(strcmp(arg,"output")==0) {
		returner = LOW;
	}
	else{
		printk("argument is not 'input' or 'output', check and try again\n");
	}
	return returner;
}

void execute_set_command(uint32_t argument, struct pin_info pin) {	
	if(argument ==HIGH || argument == LOW)
	{
		if(write_output_pin_value(pin, argument)) {
			printk("succes");
		}
		else
		{
			printk("no succes");
		}
	}
	else
	{
		printk("value of output is not supported");
	}
}

void execute_get_command(struct pin_info pin) {
	int16_t pin_value = ERROR;
	pin_value = read_input_pin_value(pin);
	print_value(pin_value);
}

static ssize_t sysfs_show(struct device *dev, struct device_attribute *attr, char *buffer) {
    int16_t i;
	for(i=0;i<GPIO_SIZE; i++) {
		printk("header_pin: %s direction: ",pins[i].header_pin);
		print_state(get_direction(pins[i]));
	}
     return 0;
}

static ssize_t sysfs_store(struct device *dev, struct device_attribute *attr, const char *buffer, size_t count) {
	char safe_buffer[SAFE_BUFFER_SIZE];
	char header_pin[HEADER_PIN_SIZE];
	char argument[ARGUMENT_SIZE];
	struct pin_info pin;	
	// caching the variable takes less processoing power
	// need the cast because of warning that the types are not the same.
	uint32_t minimun_length = min((size_t)14,count); 

	// copy expected max length data to a safe buffer 
	// the buffer is safe in use of sscanf 
	memcpy(safe_buffer, buffer, minimun_length);
	safe_buffer[minimun_length] = '\0';
	sscanf (safe_buffer, "%s %s", header_pin, argument);
	if(can_use_gpio(header_pin)) {
		uint32_t argument_value = convert_argument(argument);
		pin = get_gpio_info(header_pin);		
		if(argument_value != ERROR_2 && (argument_value == HIGH || argument_value == LOW)) {
			bool direction_succeded = set_gpio_direction(argument_value, pin);
			if(direction_succeded) {
				printk("succes\n");
			}
			else
			{
				printk("no succes\n");
			}
		}
		else
		{
			printk("argument not supported\n");
		}
	}
	else
	{
		printk("this pin: %s  is not a gpio pin, please try another one\n",header_pin);
	}
    return minimun_length;
}

/* 
 * This is called whenever a process attempts to open the device file 
 */
static int device_open(struct inode *inode, struct file *file) {
	uint32_t *minorNr = kmalloc(sizeof(uint32_t), GFP_KERNEL);
	//Set the minor number in the pointer
	*minorNr = MINOR(inode->i_rdev);
	//Set the private data to the pointer
	file->private_data = minorNr;
	
	MsgPtr[*minorNr] = Message[*minorNr];
	
	//Lock the module
	try_module_get(THIS_MODULE);	
	
	return SUCCESS;
}

static int device_release(struct inode *inode, struct file *file) {
	//Free the device, data and memory module
	kfree(file->private_data);
	module_put(THIS_MODULE);
	return SUCCESS;
}

static ssize_t device_read(struct file *file, char __user * buffer, size_t length, loff_t * offset) {
	printk("this action it not supported\n");
	//Return the amount of bytes read, this is always at full length, because this action isn't supported
	return length;
}

/* 
 * This function is called when somebody tries to
 * write into our device file. 
 */
static ssize_t device_write(struct file *file, const char __user * buffer, size_t length, loff_t * offset) {
	char header_pin[HEADER_PIN_SIZE];
	char command[COMMAND_SIZE];
	char safe_buffer[SAFE_BUFFER_SIZE];
	struct pin_info pin;	
	// caching the variable takes less processoing power
	// need the cast because of warning that the types are not the same.
	uint32_t minimun_length = min((size_t)HEADER_PIN_SIZE,length); 
	uint32_t argument = 0;

	// copy expected max length data to a safe buffer 
	// the buffer is safe in use of sscanf 
	memcpy(safe_buffer, buffer, minimun_length);
	safe_buffer[minimun_length] = '\0';

	sscanf (safe_buffer, "%3s%s%u", command, header_pin, &argument);
	printk("command: %s header_pin: %s argument %u \n", command, header_pin, argument);

	if(can_use_gpio(header_pin)) {
		pin = get_gpio_info(header_pin);
		if(strcmp(command,"set")==0) {
			
			execute_set_command(argument,pin);
		} 
		else if(strcmp(command,"get")==0) {
			execute_get_command(pin);
		}
		else
		{
			printk("command not supported, use 'set' or 'get' command\n");
		}
	}
	else
	{
		printk("this pin: %s  is not a gpio pin, please try another one\n",header_pin);
	}

	// because it can happen that the user puts more data in the buffer which we do not need or want.
	return length;
}

/* 
 * This line is now changed: in the previous example, the last parameter to DEVICE_ATTR
 * was NULL, now we add a store function as well. We must also add writing rights to the file:
 */
static DEVICE_ATTR(data, S_IWUGO | S_IRUGO, sysfs_show, sysfs_store);

/*
 * This is identical to previous example.
 */
static struct attribute *attrs[] = {
    &dev_attr_data.attr,
    NULL   /* need to NULL terminate the list of attributes */
};

static struct attribute_group attr_group = {
    .attrs = attrs,
};

static struct kobject *hello_obj = NULL;

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

int __init sysfs_init(void) {
    int result = 0;
    int ret_val = 0;

	init_registers();
    /*
     * This is identical to previous example.
     */
    hello_obj = kobject_create_and_add(sysfs_dir, kernel_kobj);
    if (hello_obj == NULL)
    {
        printk (KERN_INFO "%s module failed to load: kobject_create_and_add failed\n", sysfs_file);
        return -ENOMEM;
    }

    result = sysfs_create_group(hello_obj, &attr_group);
    if (result != 0)
    {
        /* creating files failed, thus we must remove the created directory! */
        printk (KERN_INFO "%s module failed to load: sysfs_create_group failed with result %d\n", sysfs_file, result);
        kobject_put(hello_obj);
        return -ENOMEM;
    }

	//Register the character device (atleast try)
	ret_val = register_chrdev(MAJOR_NUM, DEVICE_NAME, &Fops);

	//Negative values signify an error
	if (ret_val < 0) {
		printk(KERN_ALERT "%s failed with %d\n", "Sorry, registering the character device ", ret_val);
		return ret_val;
	}

	printk(KERN_INFO "%s The major device number is %d.\n", "Registeration is a success", MAJOR_NUM);
    printk(KERN_INFO "/sys/kernel/%s/%s created\n", sysfs_dir, sysfs_file);
    return 0;
}

void __exit sysfs_exit(void) {
    kobject_put(hello_obj);
    unregister_chrdev(MAJOR_NUM, DEVICE_NAME);
    printk (KERN_INFO "/sys/kernel/%s/%s removed\n", sysfs_dir, sysfs_file);
}

// sys fs
module_init(sysfs_init);
module_exit(sysfs_exit);
MODULE_DESCRIPTION("Read/Write GPIO");
