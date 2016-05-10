
CC=gcc
CFLAGS= -std=gnu99 -Wall -g
EXEC=tetris

all: $(EXEC)



tetris: tetris.o affichage.o brique.o jeu.o
	$(CC) $(CFLAGS) -o $@ $^ 


%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< 
		

clean :
	rm -rf *.o

mrproper :
	rm -rf $(EXEC)
