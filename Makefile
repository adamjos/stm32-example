# Directories
SRC_DIR = src
INC_DIR = inc
LIB_DIR = $(INC_DIR)
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

# Files
TARGET = $(BIN_DIR)/app

SOURCES = main.c \
		  led.c \

OBJECT_NAMES := $(SOURCES:.c=.o)
OBJECT_NAMES := $(OBJECT_NAMES:.s=.o)
OBJECTS = $(patsubst %,$(OBJ_DIR)/%,$(OBJECT_NAMES))

# Toolchain
CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
BIN = arm-none-eabi-objcopy
STL = st-flash
CPPCHECK = cppcheck

#  Flags
WFLAGS = -Wall -Wextra -Werror -Wshadow
CFLAGS = -mthumb -mcpu=cortex-m33 $(WFLAGS) \
	$(addprefix -I,$(INC_DIR)) -Og -g
LINKER_SCRIPT = linker.ld
LDFLAGS =  -T $(LINKER_SCRIPT) $(addprefix -L,$(LIB_DIR))


all: $(TARGET).bin

listsrc:
	echo $(SOURCES)

listobj:
	echo $(OBJECTS)

# Compiling assembly files
$(OBJ_DIR)/%.o: %.s
	@mkdir -p $(dir $@)
	$(AS) $^ -o $@

# Compiling C files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $^ -o $@

# Linking
$(TARGET).elf: $(OBJ_DIR)/crt.o $(OBJECTS)
	@mkdir -p $(dir $@)
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@

# Convert to binary
$(TARGET).bin: $(TARGET).elf
	$(BIN) -O binary $^ $@

.PHONY: all clean flash erase reset check

clean:
	rm -f *.o *.elf *.bin -r $(BUILD_DIR)/*

flash: $(TARGET).bin
	$(STL) write $^ 0x8000000

erase:
	$(STL) erase

reset:
	$(STL) reset

check:
	@$(CPPCHECK) --quiet --enable=all --error-exitcode=1 \
	 --inline-suppr \
	 --suppress=missingIncludeSystem \
	-I $(INC_DIR)/ \
	-I /usr/include/ \
	-I /usr/local/include/ \
	$(SRC_DIR)/ \