#include <avr/io.h>
#include <util/delay.h>

int blink(int n)
{
    for (int i = 0; i < n; i++)
    {
        PORTB |= (1 << PORTB5);
        _delay_ms(1000);
        PORTB &= ~(1 << PORTB5);
        _delay_ms(1000);
    }
}

int setup()
{
    // OPTIONAL: Enable PORTB5 as output
    DDRB = DDRB | (1 << DDB5);

    return 0;
}
