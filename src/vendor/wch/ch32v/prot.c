#include <stdint.h>

#define FLASH_OBKEYR ((volatile uint32_t *)0x40022008)
#define FLASH_KEYR ((volatile uint32_t *)0x40022004)
#define FLASH_CTLR ((volatile uint32_t *)0x40022010)
#define FLASH_STATR ((volatile uint32_t *)0x4002200C)
#define RDPRT_KEY 0x000000A5
#ifndef FLASH_KEY1
#define FLASH_KEY1 0x45670123
#endif

#ifndef FLASH_KEY2
#define FLASH_KEY2 0xCDEF89AB
#endif

#define FLASH_ADDR ((volatile uint32_t *)0x40022014)
#define FLASH_OBR ((volatile uint32_t *)0x4002201C)
#define FLASH_RDPR (*FLASH_OBR & (1 << 1))
#define RDPR ((volatile uint16_t *)0x1FFFF800)
#define RDPR_ON 0x1331
#define RDPR_OFF 0x5AA5

static void unlockFlashCTLR()
{
    *FLASH_KEYR = FLASH_KEY1;
    *FLASH_KEYR = FLASH_KEY2;
}

static void unlockFlashOBKEYR()
{
    *FLASH_OBKEYR = FLASH_KEY1;
    *FLASH_OBKEYR = FLASH_KEY2;
}

static void userSelectProg()
{
    unlockFlashCTLR();
    unlockFlashOBKEYR();

    while (*FLASH_STATR != 0x8000) ;

    // Set OBG
    *FLASH_CTLR |= 1 << 4;
}

static void _lockFlash()
{
    *FLASH_KEYR = RDPRT_KEY;
    *RDPR = RDPR_ON;
}

static void _unlockFlash()
{
    *RDPR = RDPR_OFF;
}

int lockFlash()
{
    if (!FLASH_RDPR)
    {
        userSelectProg();
        _lockFlash();
    }

    return 0;
}

int unlockFlash()
{
    if (FLASH_RDPR)
    {
        userSelectProg();
        _unlockFlash();
    }

    return 0;
}
