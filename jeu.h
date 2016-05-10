#ifndef JEU_H
#define JEU_H
#include "affichage.h"
#include "brique.h"
#include <poll.h>
#define PATHSIZE 256

void restore_term(struct termios *save);
int set_term(struct termios *original);


int jeu1(char *nom);

void menu();
char **deroulement(char *mod);




#endif
