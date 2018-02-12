PROJECT = ring_buffer

DIST = ./dist/
BUILD = ./build/
TEST = ./test/
MOCKS = ./test/mocks/
DIRECTORIES = $(DIST) $(BUILD) $(TEST) $(MOCKS)

INCLUDE = ./include/
LIBC = ./libc/
SOURCE_FILES = $(filter-out $(wildcard $(LIBC)*_test.c), $(wildcard $(LIBC)*.c))
TEST_FILES = $(patsubst $(LIBC)%,%,$(patsubst %_test.c,%_test,$(wildcard $(LIBC)*_test.c)))


REMOVE = rm -rf
MAKE_DIR = mkdir -p
CHANGE_DIR = cd

AR = ar
CC = gcc
CFLAGS = -g -Wall
LDFLAGS = 
ARFLAGS = rsc

all: $(DIRECTORIES) $(PROJECT).a
	echo $(TEST_FILES)

$(PROJECT).a: $(PROJECT).binary
	$(AR) $(ARFLAGS) -o $(DIST)lib$@ $(BUILD)*.o



$(PROJECT).binary: $(SOURCE_FILES)
	$(CC) $(CFLAGS) $(LDFLAGS) -c $^ -I$(INCLUDE)
	mv *.o $(BUILD)

$(DIRECTORIES):
	$(MAKE_DIR) $@

tests: $(TEST_FILES)

$(TEST_FILES): %_test: $(LIBC)%.c
	$(CC) -m64 -D TEST -o $(TEST)$@.o $(LIBC)$@.c $< ./Unity/unity.c -Imocks/ -I$(INCLUDE)
	$(TEST)$@.o

clean:
	$(REMOVE) $(DIST) $(BUILD)
	$(REMOVE) $(TEST)*.o