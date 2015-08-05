/*
 * header file made to store all the defines needed for the GPIO
 */


#define MAJOR_NUM 100
#define SUCCESS 0
#define DEVICE_NAME "GPIO"
#define MSG_LEN 10
#define EMC_D_SEL 3
#define LCD_POWER_PIN 11
#define INPUT 0
#define OUTPUT 1

#define LCD_CTRL				0x31040018 	// this register is used to disable the lcd
 											// when disabled it will not interfere with gpio registers.


//Port 0
#define P0_INPUT_STATE 			0x40028040 //Reads the state of input pins. - RO
#define P0_OUTPUT_SET 			0x40028044 //Output pin set register. Allows setting output pin(s). - WO
#define P0_OUTPUT_CLR 			0x40028048 //Output pin clear register. Allows clearing output pin(s). - WO
#define P0_OUTPUT_STATE 		0x4002804C //Output pin state register. Reads the state of output pins. - RO
#define P0_DIRECTION_SET 		0x40028050 //direction set register. Configures P0 I/O pins as outputs. - WO
#define P0_DIRECTION_CLR 		0x40028054 //direction clear register. Configures P0 I/O pins as inputs. - WO
#define P0_DIRECTION_STATE 		0x40028058 //direction state register. Reads direction of P0 I/O pins. 0 RO

#define P0_MUTEX_SET 			0x40028120 //multiplexer set register. selects alternate functions on certain Port 0 pins. - WO
#define P0_MUTEX_CLR 			0x40028124 //multiplexer clear register. selects default GPIO function on certain pins. - WO
#define P0_MUTEX_STATE 			0x40028128 //multiplexer state register. Reads selection of alternate or I/O functions on Port 0 pins. RO

//Port 1
#define P1_INPUT_STATE 			0x40028060 //Input pin state register. Reads the state of P1 pins. - RO
#define P1_OUTPUT_SET 			0x40028064 //Output pin set register. Sets output value of P1 pins. - WO
#define P1_OUTPUT_CLR 			0x40028068 //Output pin clear register. Clears output value of P1 pins. - WO
#define P1_OUTPUT_STATE 		0x4002806C //Output pin state register. Reads state of P1 output pins. - RO
#define P1_DIRECTION_SET 		0x40028070 //direction set register. Configures Port 1 I/O pins as outputs. - WO
#define P1_DIRECTION_CLR 		0x40028074 //direction clear register. Configures Port 1 I/O pins as inputs. - WO
#define P1_DIRECTION_STATE 		0x40028078 //direction state register. Reads direction value Port 1 I/O pins. 0 RO

#define P1_MUTEX_SET 			0x40028130 //Port 1 multiplexer set register. selects alternate functions on certain Port 1 pins. - WO
#define P1_MUTEX_CLR 			0x40028134 //Port 1 multiplexer clear register. selects default GPIO function on certain Port 1 pins. - WO
#define P1_MUTEX_STATE 			0x40028138 //Port 1 multiplexer state register. Reads selection of alternate or I/O functions on Port 1 pins. RO

//Port 2
#define P2_INPUT_STATE 			0x4002801C //Input pin state register. Reads the state of Port 2 GPIO pins. - RO
#define P2_OUTPUT_SET 			0x40028020 //Output pin set register. Sets Port 2 GPIO output value. - WO
#define P2_OUTPUT_CLR 			0x40028024 //Output pin clear register. Clears Port 2 GPIO output value. - WO
#define P2_3_DIRECTION_SET 		0x40028010 //Port 2 and Port 3 GPIO direction set register. configures direction of I/O pins P2.[23:0] and GPIO_[5:0]. - WO
#define P2_3_DIRECTION_CLR 		0x40028014 //Port 2 and Port 3 GPIO direction clear register. configures direction of I/O pins P2.[23:0] and GPIO_[5:0]. - WO
#define P2_3_DIRECTION_STATE 	0x40028018 //Port 2 and Port 3 GPIO direction state register. Reads pin direction status for I/O pins P2.[23:0] and GPIO_[5:0].  RO

#define P2_MUTEX_SET 			0x40028028 //multiplexer set register. selects alternate functions on certain Port 2 pins.- WO
#define P2_MUTEX_CLR 			0x4002802C //multiplexer clear register. selects default GPIO functions oncertain Port 2 pins. - WO
#define P2_MUTEX_STATE 			0x40028030 //multiplexer state register.Reads selection of alternate or I/O functions on Port 2 pins. RO

//Port 3
#define P3_INPUT_STATE			0x40028000 //Port 3 Input pin state register. Reads the state of GPIO[5:0] and GPI input pins. - RO
#define P3_OUTPUT_SET 			0x40028004 //Port 3 output pin set register. Sets GPIO[5:0] output and GPO_[23:0] pin(s). - WO
#define P3_OUTPUT_CLR 			0x40028008 //Port 3 output pin clear register. Clears GPIO_[5:0] output and GPO_[23:0] pin(s). - WO
#define P3_OUTPUT_STATE			0x4002800C //Port 3 output pin state register. Reads the state of GPIO_[5:0] output and GPO_[23:0] pin(s). - RO

#define P3_MUTEX_SET 			0x40028110 //Port 3 multiplexer set register. Controls the selection of alternate functions on Port 3 pins. - WO
#define P3_MUTEX_CLR 			0x40028114 //Port 3 multiplexer clear register. selects default GPIO functions on certain Port 3 pins. - WO
#define P3_MUTEX_STATE 			0x40028118 //Port 3 multiplexer state register. Reads selection of alternate or I/O functions on Port 3 pins. - RO

typedef enum {P0, P1, P2, P3} Port;

struct pin_info {
   char * header_pin;
   Port port;
   uint16_t input_bit;
   uint16_t output_bit;
};