CC = clang
CFLAGS = -Wall -Wextra -I.

binaryfile : reg16bitprj.o registers_utils.o
	@$(CC) -o $@ $^
%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -rf *.o binaryfile
