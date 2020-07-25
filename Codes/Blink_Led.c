#define F_CPU 16000000UL

#include <avr/io.h> // This contains the definitions of the terms used
#include <util/delay.h> // This contains the definition of delay function

int main (void)
{
	DDRD =  0b00000100; // Port D2 (Pin 4 in the ATmega) made output
	PORTD = 0b00000000; // Turn LED off
	uint8_t i = 0; 
	while(1)
	{
		PORTD = PORTD << 1;
		_delay_ms(100);
		
		if(i > 3)
		{
			i =0;
			PORTD = 0b00000001;
		}
		i++;
	}
	return 0;
}
