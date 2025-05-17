CC = clang
CFLAGS = -Wall -Wextra -I.

binaryfile : multireg.o registers_utils.o
	@$(CC) -o $@ $^
%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -rf *.o binaryfile
