CFLAGS:=-Iinclude/

SRCS:=main.c

all: rom-${MCU}.elf
flash: flash_mcu
clean: clean_mcu
	rm -f rom rom.bin rom.elf rom.hex rom.lst rom.map

include vendor/${VENDOR}/${MCU}/makefile.mk
