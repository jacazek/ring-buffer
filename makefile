PROJECT = ring_buffer
MCU_TARGET     = atmega2560


DIST = ./dist/
BUILD = ./build/
TEST = ./test/
MOCKS = ./test/mocks/
DIRECTORIES = $(DIST) $(BUILD) $(TEST) $(MOCKS)

INCLUDE = ./include/
LIBC = ./libc/
SOURCE_FILES = $(filter-out $(wildcard $(LIBC)*_test.c), $(wildcard $(LIBC)*.c))
TEST_FILES = $(patsubst $(LIBC)%,%,$(patsubst %_test.c,%_test,$(wildcard $(LIBC)*_test.c)))

OPTIMIZE = -Os

REMOVE = rm -rf
MAKE_DIR = mkdir -p
CHANGE_DIR = cd

AR = avr-ar
CC = avr-gcc
GCC = gcc
CFLAGS = -g -Wall $(OPTIMIZE) -ffunction-sections -mmcu=$(MCU_TARGET)
LDFLAGS = 
ARFLAGS = rsc
OBJCOPY = avr-objcopy


all: $(DIRECTORIES) $(PROJECT).a


$(PROJECT).a: $(PROJECT).binary
	$(AR) $(ARFLAGS) -o $(DIST)lib$@ $(BUILD)*.o


$(PROJECT).binary: $(SOURCE_FILES)
	$(CC) $(CFLAGS) -c $(LDFLAGS) $^ -I$(INCLUDE)
	mv *.o $(BUILD)



$(DIRECTORIES):
	$(MAKE_DIR) $@

tests: $(TEST_FILES)

$(TEST_FILES): %_test: $(LIBC)%.c
	$(GCC) -m64 -D TEST -o $(TEST)$@.o $(LIBC)$@.c $< ./Unity/unity.c -Imocks/ -I$(INCLUDE)
	$(TEST)$@.o

example: example/main.c main.hex

$(BUILD)main.elf: example/main.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o main.elf $< -I$(INCLUDE) -L$(DIST) -lring_buffer
	mv *.elf $(BUILD)

main.hex: $(BUILD)main.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $(DIST)$@

clean:
	$(REMOVE) $(DIST) $(BUILD)
	$(REMOVE) $(TEST)*.o