TARGET = comunication

LD_PRELOAD_LIB = arduino_hook.so

MAIN_SRCS = comunication.c

MAIN_OBJS = $(MAIN_SRCS:.c=.o)

HOOK_SRCS = arduino_hook.c

CC = gcc

CFLAGS = -Wall -Wextra
HOOK = -Wall -Wextra -fPIC -D_GNU_SOURCE

all: $(TARGET) $(LD_PRELOAD_LIB)

$(TARGET): $(MAIN_OBJS)
	$(CC) $(MAIN_OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LD_PRELOAD_LIB): $(HOOK_SRCS)
	$(CC) $(HOOK) -shared $< -o $@

clean:
	rm -f $(TARGET) $(LD_PRELOAD_LIB) $(MAIN_OBJS) $(HOOK_SRCS:.c=.o)

.PHONY: all clean
