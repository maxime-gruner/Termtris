
CC=gcc
CFLAGS= -std=gnu99 -Wall -Werror -o
EXEC=tetris

all: $(EXEC)

tetris.o: tetris.c
	$(CC) $(CFLAGS) tetris.o -c tetris.c
	
tetris: tetris.o
	$(CC) $(CFLAGS) tetris tetris.o

clean :
	rm -rf *.o

mrproper :
	rm -rf $(EXEC)
