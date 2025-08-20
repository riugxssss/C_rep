CC = gcc
CFLAGS = -Wall -g -O2

TARGET = avltree

all: $(TARGET)

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
%.o: %.c
	$(CC) $(CFLAGS) -c  $<
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
