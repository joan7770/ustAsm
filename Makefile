# Joan Marin-Romero
CC=gcc
CFLAGS=-std=c99

all: assembler
	$(CC) $(CFLAGS) $(INC) assembler.o -o assembler

assembler:
	$(CC) $(CFLAGS) $(INC) -c main.c -o assembler.o

clean:
	rm *.o *.out assembler
