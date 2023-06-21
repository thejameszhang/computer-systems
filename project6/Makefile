# Name: James Zhang
# UID: 118843940
# Directory ID: jzhang72

CC = gcc
CFLAGS = -ansi -Wall -g -O0 -Wwrite-strings -Wshadow -pedantic-errors -fstack-protector-all -Wextra

.PHONY: all clean

all: d8sh

parser.tab.o: parser.tab.c parser.tab.h command.h
	$(CC) $(CFLAGS) -c parser.tab.c

executor.o: executor.c executor.h command.h
	$(CC) $(CFLAGS) -c executor.c

lexer.o: lexer.c lexer.h
	$(CC) $(CFLAGS) -c lexer.c

d8sh.o: d8sh.c lexer.h executor.h
	$(CC) $(CFLAGS) -c d8sh.c

d8sh: d8sh.o parser.tab.o lexer.o executor.o
	$(CC) -o d8sh -lreadline d8sh.o parser.tab.o executor.o lexer.o

clean: 
	rm -rf d8sh *.o