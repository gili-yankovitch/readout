# Define the microcontroller, clock frequency, and programmer
MCU = atmega328p
F_CPU = 16000000UL
# PROGRAMMER = arduino
PROGRAMMER = stk500v1
BAUDRATE = 115200
PORT = /dev/ttyUSB0 # Adjust if necessary for your system

# Define the toolchain paths (adjust if necessary)
CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude
AVRDUDE_CONF = "/etc/avrdude.conf"

# Define the file names
TARGET = rom
SRC:= $(SRCS) vendor/atmel/framework/bsp.c vendor/atmel/328p/prot.c
OBJ = $(TARGET).o
ELF = $(TARGET).elf
HEX = $(TARGET).hex

# Define the compilation flags
CFLAGS:= $(CFLAGS) -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -std=c11
LDFLAGS = -mmcu=$(MCU) -Wl,--section-start=.bootloader=0x7000
# LDFLAGS = -mmcu=$(MCU)

# Compile the source code
$(ELF): $(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRC) -o $(ELF)

# Convert ELF to HEX
$(HEX): $(ELF)
	$(OBJCOPY) -O ihex $(ELF) $(HEX)

# Upload the HEX file using avrdude
flash_mcu: $(HEX)
	$(AVRDUDE) -C $(AVRDUDE_CONF) -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUDRATE) -U flash:w:$(HEX):i -U hfuse:w:0xD8:m -U lfuse:w:0xFC:m

erase:
	$(AVRDUDE) -C $(AVRDUDE_CONF) -v -p $(MCU) -c $(PROGRAMMER) -P $(PORT) -b $(BAUDRATE) -e -Ulock:w:0xFF:m -Uefuse:w:0xFD:m -Uhfuse:w:0xDA:m -Ulfuse:w:0xFC:m

# Clean build files
clean_mcu:
	rm -f $(OBJ) $(ELF) $(HEX)

# Phony targets
.PHONY: clean_mcu flash_mcu
