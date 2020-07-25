// http://www.rjhcoding.com/avrc-uart.php

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BAUDRATE 9600
#define BAUD_PRESCALLER ((F_CPU / (BAUDRATE * 16UL)) - 1)

void USART_init(void);
void UART_putc(unsigned char data);
char UART_getc(void);

uint16_t volatile delay_in_ms = 1000;

int main(void)
{
	USART_init(); //Call the USART initialization code

	while (1)
	{
		UART_putc(UART_getc());
	}

	return 0;
}

void USART_init(void)
{
	UBRR0L = (uint8_t)(BAUD_PRESCALLER); // (uint8_t)(103 & 0xFF); lower byte is just 103

	UBRR0H = (uint8_t)(BAUD_PRESCALLER >> 8);

	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = (3 << UCSZ00);
}

char UART_getc(void)
{
	// wait for data
	while (!(UCSR0A & (1 << RXC0)))
		;

	// return data
	return UDR0;
}

void UART_putc(unsigned char data)
{
	if (data == 0x00)
		return;

	while (!(UCSR0A & (1 << UDRE0)))
		; // wait to be ready

	UDR0 = data;
}
