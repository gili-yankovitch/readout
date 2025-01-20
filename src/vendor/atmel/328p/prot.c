#include <avr/io.h>
#include <util/delay.h>

static void cli()
{
    __asm__ volatile ("cli" ::: "memory");
}

static void sei()
{
    __asm__ volatile ("sei" ::: "memory");
}

static int readLockStatus()
{
    unsigned int v;

    __asm__("ldi ZL, 1");
    __asm__("ldi ZH, 0");

    __asm__("ldi    r16, %0" :: "I" ((1 << SPMEN) | (1 << BLBSET)));
    __asm__("out    %0, r16" :: "I" (_SFR_IO_ADDR(SPMCSR)));
    __asm__("lpm");

    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");

    __asm__("mov %0, r0" : "=r" (v) :: "r16");

    return v;
}

// For this to work, this MUST be executed BEFORE application main()
// in BOOTLOADER mode. Otherwise, SPM does not work.
// For THIS to work, [hfuse] must have BOOTRST | BOOTSZ0 | BOOTSZ1 (= 0xX8)
// placing bootloader from 0x0700 and boot from bootloader.
int __attribute__((section(".bootloader"))) lockFlash()
{
    cli();

    // Locking EVERYTHING from bootloader access: 0xc0 - 0b11000000
    // BLB12:0 BLB11:0
    //  SPM is not allowed to write to the boot loader section, and LPM executing
    //  from the application section is not allowed to read from the boot loader
    //  section. If interrupt vectors are placed in the application section, interrupts
    //  are disabled while executing from the boot loader section.
    // BLB02:0 BLB01:0
    //  SPM is not allowed to write to the application section, and LPM executing
    //  from the boot loader section is not allowed to read from the application
    //  section. If interrupt vectors are placed in the boot loader section, interrupts
    //  are disabled while executing from the application section.
    //  SPM is not allowed to write to the application section.
    // LB2:0 LB1: 0 - No external reads or writes allowed.
    // Reset is either through the unlockFlash below (not recommended) or through a
    // FULL chip erase.
    if (readLockStatus() == 0xc0)
    {
        // Don't have to do anything
        goto done;
    }

    __asm__("ldi ZL, 1");
    __asm__("ldi ZH, 0");

    __asm__("ldi r16, 0xc0");
    __asm__("mov r0, r16");

    __asm__("ldi    r16, %0" :: "I" ((1 << SPMEN) | (1 << BLBSET)));
    __asm__("out    %0, r16" :: "I" (_SFR_IO_ADDR(SPMCSR)));
    __asm__("spm");

    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");

    sei();

done:
    return 0;
}

int unlockFlash()
{
    cli();

    // Unlocking everything with passthrough between Bootloader and Application: 0xff - 0b11111111
    __asm__("ldi ZL, 1");
    __asm__("ldi ZH, 0");

    __asm__("ldi r16, 0xff");
    __asm__("mov r0, r16");

    __asm__("ldi    r16, %0" :: "I" ((1 << SPMEN) | (1 << BLBSET)));
    __asm__("out    %0, r16" :: "I" (_SFR_IO_ADDR(SPMCSR)));
    __asm__("spm");

    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");

    sei();

    return 0;
}
