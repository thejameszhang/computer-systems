# Name: James Zhang
# UID: 118843940
# Course: CMSC216 by Professor Yoon
# Section: 0301

CC = gcc
CFLAGS = -ansi -Wall -g -O0 -Wwrite-strings -Wshadow -pedantic-errors -fstack-protector-all -Wextra
PROGS = shell_jr
.PHONY: all clean
all: $(PROGS)

shell_jr: shell_jr.o
	$(CC) -o shell_jr shell_jr.o

shell_jr.o: shell_jr.c
	$(CC) $(CFLAGS) -c shell_jr.c

clean:
	@rm -f *.o $(PROGS) *.tmp