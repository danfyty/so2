C_FLAGS=-std=c99
CC=gcc

open_write: open_write.c utils.h
	$(CC) $(C_FLAGS) open_write.c -o open_write

clean:
	rm *.o open_write
