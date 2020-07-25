#include <avr/io.h>
#include <avr/interrupt.h>

int extraTime = 0;

int main(void) {
    
    TCCR0A = 0b00000010;    // C1:: timer 0 mode 2 - CTC
    TCCR0B = 0b00000100;    // C2:: set prescaler to 256
    OCR0A = 250;            // C3:: number of ticks in Output Compare Register
    TIMSK0 = 0b00000010;    // C4:: trigger interrupt when ctr (TCNT0) >= OCR0A

    DDRB = 0b00010000;      // LED (D12) as an output 
    sei();                 
   
    while(1) {
        //Nothing todo here.
	}

    return 0;
}

ISR(TIMER0_COMPA_vect) {    
    extraTime++;
   
    if (extraTime > 200) {
        PORTB ^= (1<<PORTB4); // toggle LED
        extraTime = 0;       
    }
}