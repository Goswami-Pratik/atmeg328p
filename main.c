// http://www.rjhcoding.com/avrc-uart.php

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#define BAUDRATE 9600
#define BAUD_PRESCALLER ((F_CPU / (BAUDRATE * 16UL)) - 1)

//Declaration of our functions
void TIMER_init();
void USART_init(void);
char UART_getc_if_available(void);
void blink();
bool can_read();

uint16_t volatile delay_in_ms = 1000;

int main(void)
{
	TIMER_init();
	USART_init();

	DDRD = 0b00000100;	// Port D2 
	PORTD = 0b00000000; // Turn LED off

	sei();

	while (1)
	{
		blink();
	}

	return 0;
}

ISR(TIMER0_COMPA_vect)
{
	char mode = UART_getc_if_available();

	if (mode == 0x00)
		return;

	if (mode == 'H')
	{
		delay_in_ms = 100;
		return;
	}

	if (mode == 'L')
	{
		delay_in_ms = 1500;
		return;
	}
}

void blink()
{
	PORTD = 0b00000100;
	_delay_ms(delay_in_ms);
	PORTD = 0b00000000;
	_delay_ms(delay_in_ms);
}

void TIMER_init()
{
	TCCR0A = 0b00000010; // C1:: timer 0 mode 2 - CTC
	TCCR0B = 0b00000100; // C2:: set prescaler to 256
	OCR0A = 250;		 // C3:: number of ticks in Output Compare Register
	TIMSK0 = 0b00000010; // C4:: trigger interrupt when ctr (TCNT0) >= OCR0A
}

void USART_init(void)
{
	UBRR0L = (uint8_t)(BAUD_PRESCALLER);

	UBRR0H = (uint8_t)(BAUD_PRESCALLER >> 8);

	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = (3 << UCSZ00);
}

char UART_getc_if_available()
{
	if (can_read())
		return UDR0;

	return 0x00;
}

bool can_read()
{
	return ((UCSR0A & (1 << RXC0)));
}
