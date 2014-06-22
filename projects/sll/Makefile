#
# Filename: Makefile
# Author:  Bhagat Janarthanan
#

SLL := obj/sll
LIBS := -lm
CC := gcc
CFLAGS := -g -Wall

.PHONY: default all clean

default: $(SLL)
all: default

OBJECTS := $(patsubst %.c, obj/%.o, $(wildcard src/*.c))
HEADERS := $(wildcard src/*.h)

obj/%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(SLL) $(OBJECTS)

$(SLL): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f obj/*.o
	-rm -f $(SLL)
