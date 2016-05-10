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

}brique;

brique read_brique(int fd);
void aff_brique(brique *b);


#endif