#define SLIDER A1

#define BUZZER   3
#define DATA     4
#define LED1     5
#define LED2     6
#define LATCH    7
#define CLOCK    8
#define BUTTON2  11

volatile bool ledstate = false;
volatile bool dot = false;

volatile uint8_t charnumber = 0; 

volatile byte dotcounter = 0;

int slider_value = 0;

const uint8_t displayCharSet[] = 
{
	// each byte represent one appearance of the 8-segment display
	// each bit in a byte represent one segment of the 8-segment display
	// Numbers 0 to 9
    B00111111,B00000110,B01011011,B01001111,B01100110,B01101101,B01111101,B00000111,B01111111,B01101111,
	//A to F
	B01110111, B01111111, B00111001, B00111111, B01111001, B01110001,
	//point:
	B10000000
};

void inc_8segment(void)
{
	charnumber++;
	charnumber = charnumber % 16;
}

void writeChar(uint8_t thechar)
{
	digitalWrite(LATCH,LOW);
	shiftOut(DATA,CLOCK,MSBFIRST,~(thechar));  
	digitalWrite(LATCH,HIGH);
}

// Interrupt triggered on button 2
ISR(PCINT0_vect) 
{
	ledstate = !digitalRead(BUTTON2);
}

// Interrupt triggered when Timer 1 reaches OCR1A
ISR(TIMER1_COMPA_vect)
{
	inc_8segment();
}

// Interrupt triggered when Timer 2 overflows
ISR(TIMER2_OVF_vect)
{
	// Timer 2 runs pretty fast, so use dotcounter's overflow as a trigger to actually go
	if (dotcounter++ == 0) 
	{
		dot = !dot;
	}
}

void setup()
{
	pinMode(BUTTON2, INPUT);

	digitalWrite(BUTTON2, HIGH);

	pinMode(LED1, OUTPUT);
	digitalWrite(LED1, LOW);

	pinMode(LATCH, OUTPUT);
	pinMode(CLOCK, OUTPUT);
	pinMode(DATA, OUTPUT);
  
	pinMode(SLIDER, INPUT);

	/* When the PCIE0 bit is set (one) and the I-bit in the Status Register (SREG) is set (one), pin
	change interrupt 0 is enabled. Any change on any enabled PCINT7..0 pin will cause an interrupt.  
	(page 73 of datasheet) */
	PCICR  |= _BV (PCIE0);   // enable pin change interrupts the relevant range of d-pins
	PCMSK0 |= _BV(PCINT3);   // Enable pin change interrupt for PCINT3 (D11)

	// Timer control registers
	TCCR1A = 0; // Clear all settings
	TCCR1B = 0;

	TCCR2A = 0;
	TCCR2B = 0;

	// Clock speed is 16MHz, so 1 clock tick (1/16MHz) = 62,5 ns (nano seconds)
	// prescaler of 256 makes a timer tick 256x slower = 16 us (micro seconds)
	// timer overflow after 0xffff timer ticks         = 1.05 s

	TCCR1B |= _BV(CS10);  // Prescaler to 64 instead of 256
	TCCR1B |= _BV(CS11);

	TCCR2B |= (_BV(CS20) | _BV(CS22)); // Prescaler to 1024 for Timer 2

	// Enable CTC/OCR1A compare mode on timer 1
	TCCR1B |= _BV(WGM12); // Turn on CTC on OCR1A
	TCCR1A |= _BV(COM1A1); // "Clear OC1A/OC1B on Compare Match when upcounting. "

	// timer interrupts
	TIMSK1 = 0;             // Reset Timer 1 interrupt mask
	TIMSK1 |= _BV(OCIE1A);  // Enable output compare interrupt

	TIMSK2 = 0;				// Reset Timer 2 interrupt mask
	TIMSK2 |= _BV(TOIE2);   // Enable overflow interrupt for timer 2

	TIFR1 |= _BV(TOV1);    // clear any outstanding interrupts
	TIFR2 |= _BV(TOV2);
	PCIFR |= _BV(PCIF0);
}

void loop()
{
	static bool olddot = false;
	static uint8_t oldchar = 0;
	// Only change the speed (OCR1A) when it's changed more than 10.  
	int slidernow = analogRead(SLIDER);
	if (abs(slidernow - slider_value) > 10)
	{
		// Hold interrupts while writing to OCR1A
		cli();
		OCR1A = slidernow * 64;
		sei();
		slider_value = slidernow;
	}

	if (olddot != dot || oldchar != charnumber) {
		// Add the dot (0b10000000) if dot
		if (dot) {
			writeChar(displayCharSet[charnumber] | displayCharSet[16]);
		} else {
			writeChar(displayCharSet[charnumber]);
		}
		olddot = dot;
		oldchar = charnumber;
	}

	// Turn led on or off, ledstate is changed in interrupts
	digitalWrite(LED1, ledstate);
}






