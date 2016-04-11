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
#include "brique.h"

#define HAUTEUR 28 //taille par defaut du jeu entier

/* Structure representant la map*/
typedef struct level{
	int largeur; //largeur de le map
	int hauteur; //hauteur de la map
	char **map; //map
	
	int n_brique;
	brique *brique_type; //tableau de taille n type de brique
	
}level;

level *read_level(int fd);


void aff_map(level *m);






#endif
