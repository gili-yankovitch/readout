#include <ch32v003fun.h>

int blink(int n)
{
    for (int i = 0; i < n; ++i)
    {
    	funPinMode( PC3, GPIO_Speed_10MHz | GPIO_CNF_OUT_PP );
        funDigitalWrite(PC3, FUN_HIGH);
        Delay_Ms(500);
        funDigitalWrite(PC3, FUN_LOW);
        Delay_Ms(500);
    }

    return 0;
}

int setup()
{
	SystemInit();

	// Enable GPIOs
	funGpioInitAll();

    // Optional: For blinking LED
	funPinMode(PC3, GPIO_Speed_10MHz | GPIO_CNF_OUT_PP);

    return 0;
}
