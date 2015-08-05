both the PWM and GPIO (Pulse Width Modulation) were made for the LPC 3250 developer's kit.
They're both kernel modules meant to controll and read the hardware with the help of the registers.
The registry addresses and values can be found within the manual of the LPC 3250.
note: both these applications can be compiled with a cross compiler which is not included here.
However, they have been tested and do function as intended.

The PWM kernel module allows users to set a PWM signal on a pin on the LPC 3250 board.
The set values can also be read back by the user with the correct commands.
The 3 values that can be set and read are:
- enable/disable
- frequency
- duty

All these values are set by writing the correct bits in the registers.
 
The GPIO kernel module allows users to set the pins on the LPC 3250 board to either input or output.
you can define a pin as either input or output.
When it's an input pin, you can read the value, when it's an output pin you can either set it to high or low.
There is also a command to print the direction of all the pins.