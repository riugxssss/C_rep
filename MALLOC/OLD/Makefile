CC = gcc
CFLAGS = -Wall -Wextra -g
AR = ar
ARFLAGS = rcs

# Targets
TARGET = main
LIB = libmy_malloc.a

# Files
OBJS = my_malloc.o
MAIN = main.o

.PHONY: all clean

all: $(TARGET)

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(TARGET): $(MAIN) $(LIB)
	$(CC) $(CFLAGS) -o $@ $^ 

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o *.a $(TARGET)
