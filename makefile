PROJECT = ring_buffer
MCU_TARGET     = atmega2560


DIST = ./dist/
DIST_LIB = $(DIST)lib/
DIST_LIB_AVR = $(DIST)lib-avr/
DIST_INCLUDE = $(DIST)include/
BUILD = ./build/
TEST = ./test/
MOCKS = ./test/mocks/
DIRECTORIES = $(DIST) $(BUILD) $(TEST) $(MOCKS) $(DIST_LIB) $(DIST_INCLUDE) $(DIST_LIB_AVR)

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
GAR = ar
CFLAGS = -g -Wall $(OPTIMIZE) -ffunction-sections -mmcu=$(MCU_TARGET)
GCFLAGS = -g -Wall $(OPTIMIZE) -ffunction-sections
LDFLAGS = 
ARFLAGS = rsc
OBJCOPY = avr-objcopy


all: $(DIRECTORIES) $(PROJECT)-avr.a $(PROJECT).a


# compile for avr
$(PROJECT)-avr.a: $(PROJECT)-avr
	$(AR) $(ARFLAGS) -o $(DIST_LIB_AVR)lib$@ $(BUILD)*.o
	cp $(INCLUDE)* $(DIST_INCLUDE)
$(PROJECT)-avr: $(SOURCE_FILES)
	$(CC) $(CFLAGS) -c $(LDFLAGS) $^ -I$(INCLUDE)
	mv *.o $(BUILD)

# compile for host
$(PROJECT).a: $(PROJECT).host
	$(GAR) $(ARFLAGS) -o $(DIST_LIB)lib$@ $(BUILD)*.o
	cp $(INCLUDE)* $(DIST_INCLUDE)
$(PROJECT).host: $(SOURCE_FILES)
	$(GCC) $(GCFLAGS) -c $(LDFLAGS) $^ -I$(INCLUDE)
	mv *.o $(BUILD)

# make sure directories exist
$(DIRECTORIES):
	$(MAKE_DIR) $@

# build and run tests... link to archive
tests: $(TEST_FILES)
$(TEST_FILES):
	$(GCC) -m64 -D TEST -o $(TEST)$@.o $(LIBC)$@.c ./Unity/unity.c -Imocks/ -I$(INCLUDE) -L$(DIST_LIB) -lring_buffer
	$(TEST)$@.o

example: example/main.c main.hex

$(BUILD)main.elf: example/main.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o main.elf $< -I$(DIST_INCLUDE) -L$(DIST_LIB_AVR) -lring_buffer-avr
	mv *.elf $(BUILD)

main.hex: $(BUILD)main.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $(DIST)$@

clean:
	$(REMOVE) $(DIST) $(BUILD)
	$(REMOVE) $(TEST)*.o