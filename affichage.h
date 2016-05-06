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
#include <sys/time.h>
#include <stdbool.h>

#define BUFMAX 1024	

/* Structure representant la map*/

level *read_level(int fd);
void load_deroulement(level *l,char* chaine);


void aff_map(level *m);
bool touche (level* m, brique* br);
void add_brique(level* m, brique* br);

bool line(level *m);
void suppr(level *m, int n);




#endif
