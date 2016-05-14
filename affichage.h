#ifndef AFF_H
#define AFF_H
#include "brique.h"

#define BUFMAX 1024	

level *read_level(int fd);
void load_deroulement(level *l,char* chaine);
void aff_map(level *m);
void add_brique(level* m, brique* br);
bool line(level *m);
void suppr(level *m, int n);




#endif
