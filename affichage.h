#ifndef AFF_H
#define AFF_H
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define HAUTEUR 28 //taille par defaut du jeu entier

/* Structure representant la map*/
typedef struct map{
	int largeur; //largeur de le map
	int hauteur; //hauteur de la map
	char **matrice; //map
}map;

map *read_map(int fd);


void aff_map(map *m);






#endif
