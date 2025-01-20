CFLAGS:=-Iinclude/

SRCS:=main.c

all: rom.elf
flash: flash_mcu
clean: clean_mcu
	rm -f rom rom.bin rom.elf rom.hex rom.lst rom.map

include vendor/${VENDOR}/${SOC}/makefile.mk
