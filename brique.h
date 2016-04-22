#ifndef BRI_H
#define BRI_H
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

typedef struct brique{
	char **bloc; //corps de la brique
	int l_brique; //largeur de la brique
	int h_brique; //hauteur de la brique
	int pos_x; //position de la brique (l axe x est l hauteur sur le terminal !) la position d une brique est celle de son bloc[0][0]
	int pos_y;
}brique;

brique read_brique(char* chaine);
void aff_brique(brique *b);

void move(brique *b,int x,int y);
void input(brique *b);


#endif
