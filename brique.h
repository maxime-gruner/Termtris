#ifndef BRI_H
#define BRI_H
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <string.h>
#include <poll.h>
#include <stdbool.h>

#define HAUTEUR 28 //taille par defaut du jeu entier


typedef struct point{
  char val;
  int color;
}point;


typedef struct brique{
	char **bloc; //corps de la brique
	int l_brique; //largeur de la brique
	int h_brique; //hauteur de la brique
	int pos_x; //position de la brique (l axe x est l hauteur sur le terminal !) la position d une brique est celle de son bloc[0][0]
	int pos_y;
	int color;
}brique;

/* Structure representant la map*/
typedef struct level{
	int largeur; //largeur de le map
	int hauteur; //hauteur de la map
	point **map; //map
	
	int n_brique;
	brique *brique_type; //tableau de taille n type de brique
	float speed;
	int total;
	int *deroulement;
}level;

brique read_brique(char* chaine,int c, int pos);
void aff_brique(brique *b);
void move(brique *b,int x,int y,level* m);
int input(brique *b, level* m);
void rotate(level *m,brique *b);
int touche (level* m, brique* br);


#endif
