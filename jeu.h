#ifndef JEU_H
#define JEU_H
#include "affichage.h"
#include "brique.h"
#define PATHSIZE 256

void restore_term(struct termios *save);
int set_term(struct termios *original);


int jeu1(char *nom);
int jeu_reseau(int sock, char *path);

void menu();
char **deroulement(char *mod);

void free_deroulement(char **tab );
void free_choix(char **tab,int size );
void free_map(level *m);

#endif
