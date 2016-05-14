#ifndef RES_H
#define RES_H
#include <sys/socket.h>
#include <arpa/inet.h>
#include "jeu.h"


void mode_reseau();
int creer_serveur();
int connect_serv(char *ip);
int add_brique_reseau(level* m, brique* br,int sock);

int envoi(int sock, level *l, char *msg);
int recoi(int sock, level *l);









#endif
