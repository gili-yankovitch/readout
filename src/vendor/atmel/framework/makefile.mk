# Define the microcontroller, clock frequency, and programmer
MMCU = atmega$(MCU)
PROGRAMMER = stk500v1
BAUDRATE = 115200
PORT = /dev/ttyUSB0 # Adjust if necessary for your system

# Define the toolchain paths (adjust if necessary)
CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude
AVRDUDE_CONF = "/etc/avrdude.conf"

# Define the file names
TARGET = rom-$(MCU)
SRC:= $(SRCS) vendor/atmel/framework/bsp.c vendor/atmel/framework/prot.c
OBJ = $(TARGET).o
ELF = $(TARGET).elf
HEX = $(TARGET).hex

# Define the compilation flags
CFLAGS:= $(CFLAGS) -mmcu=$(MMCU) -DF_CPU=$(F_CPU) -Os -std=c11
LDFLAGS = -mmcu=$(MMCU) -Wl,--section-start=.bootloader=0x7e00

# Compile the source code
$(ELF): $(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRC) -o $(ELF)

# Convert ELF to HEX
$(HEX): $(ELF)
	$(OBJCOPY) -O ihex $(ELF) $(HEX)

# Upload the HEX file using avrdude
flash_mcu: $(HEX)
	$(AVRDUDE) -C $(AVRDUDE_CONF) -c $(PROGRAMMER) -p $(MMCU) -P $(PORT) -b $(BAUDRATE) -U flash:w:$(HEX):i -U hfuse:w:$(HFUSE):m

erase:
	$(AVRDUDE) -C $(AVRDUDE_CONF) -v -p $(MMCU) -c $(PROGRAMMER) -P $(PORT) -b $(BAUDRATE) -e -Ulock:w:0xFF:m -Uefuse:w:0xFD:m -Uhfuse:w:0xDA:m -Ulfuse:w:0xFC:m

# Clean build files
clean_mcu:
	rm -f $(OBJ) $(ELF) $(HEX)

# Phony targets
.PHONY: clean_mcu flash_mcu
