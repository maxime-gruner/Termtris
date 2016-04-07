
CC=gcc
CFLAGS= -std=gnu99 -Wall 
EXEC=tetris

all: $(EXEC)



tetris: tetris.o affichage.o
	$(CC) $(CFLAGS) -o $@ $^ 

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< 
		

clean :
	rm -rf *.o

mrproper :
	rm -rf $(EXEC)
