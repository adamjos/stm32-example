CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
BIN = arm-none-eabi-objcopy
STL = st-flash
CFLAGS = -mthumb -mcpu=cortex-m33

all: app.bin

%.o: %.s
	$(AS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

app.elf: linker.ld crt.o main.o
	$(LD) -T linker.ld -o $@ crt.o main.o

app.bin: app.elf
	$(BIN) -O binary $^ $@

clean:
	rm -f *.o *.elf *.bin

flash: app.bin
	$(STL) write $^ 0x8000000

erase:
	$(STL) erase
