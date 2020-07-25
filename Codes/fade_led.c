#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    TCCR0A |= (1 << WGM00) | (1 << WGM01) | (1 << COM0A1);
    TCCR0B = 1;
    
    DDRD |= (1 << PD6); // D6 pin

    while (1)
    {
        _delay_ms(2000);

        for (OCR0A = 0; OCR0A < 255; OCR0A++)
            _delay_ms(5);

        for (OCR0A = 255; OCR0A > 0; OCR0A--)
            _delay_ms(5);
    }
    return 0;
}