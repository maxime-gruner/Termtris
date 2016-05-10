#include "affichage.h"

/* Prend un descripteur de fichier en entrer, va lire la map dans le fichier et la renverra dans un tableau a 2 dimensions */
level *read_level(int fd){
  int i = 0,j = 0,count = 1;
  level *m = malloc(sizeof(level));
  char buffer[BUFMAX];
  read(fd,buffer,BUFMAX); //lit les dimension
  char *s=strtok(buffer," ");
  int haut_debut = strtol(s,NULL,10); //convertis les dimensions en entier
  s=strtok(NULL,"\n");
  m->largeur = strtol(s,NULL,10);
  m->hauteur = HAUTEUR;
	
	
	
	m->map = malloc(m->largeur*m->hauteur*sizeof(point));
	for(i=m->hauteur-1; i>=0; i--){
		m->map[i] = calloc(m->largeur,sizeof(point));
	}
	
	/*Chargement de la map */
	for(i=m->hauteur-1; i>=0; i--){
		/*Bas de la map charge a partir du fichier */
		if(i>=HAUTEUR-haut_debut){
			s=strtok(NULL,"\n"); //lit toute la ligne de le map
		}
		for(j=0;j< m->largeur;j++){
			if(i<HAUTEUR-haut_debut ){
				m->map[i][j].val = '0';
			}else{
				m->map[i][j].val=s[j];
				if(s[j]=='1') m->map[i][j].color=0;
			}
		}
	}
	
	/* Chargement des briques */ 
	s=strtok(NULL,"\n");
	m->n_brique = strtol(s,NULL,10);
	m->brique_type = malloc(m->n_brique*sizeof(brique)); //initalisation tableau des type de brique
	s=strtok(NULL,"\0");
	for(i=0;i<m->n_brique;i++){
		m->brique_type[i] = read_brique(s,count); //charge les different type de brique
		count++;
	}
	
	load_deroulement(m,s); //charge la vitesse et le deroulement du jeu
	
	
	return m;
}




/* affichera la map dans le terminal */
void aff_map(level *m){
	int i=0, j=0;
	for(i=0;i<m->hauteur;i++){
		for(j=0;j< m->largeur;j++){
			if(m->map[i][j].val=='1'){
				switch(m->map[i][j].color){
				  case 0: write(1,"\033[40m\u2588\033[0m",12); break;
				  case 1: write(1,"\033[31m\u2588\033[0m",12); break;
				  case 2: write(1,"\033[32m\u2588\033[0m",12); break;
				  case 3: write(1,"\033[33m\u2588\033[0m",12); break;
				  case 4: write(1,"\033[34m\u2588\033[0m",12); break;
				  case 5: write(1,"\033[35m\u2588\033[0m",12); break;
				  case 6: write(1,"\033[36m\u2588\033[0m",12); break;
				  case 7: write(1,"\033[37m\u2588\033[0m",12); break;
				  case 8: write(1,"\033[38m\u2588\033[0m",12); break;
				  case 9: write(1,"\033[39m\u2588\033[0m",12); break;
				}
			}else if(m->map[i][j].val=='0'){
				write(1," ",1);
			}
		}write(1,"\u258F",4);
		write(1,"\n",1);
	}for(i=0;i< m->largeur;i++){
		write(1,"\u2594",4);
	}
}

void load_deroulement(level *l,char* chaine){
	char *s=NULL; int i=0;
	s=strtok(chaine," "); float speed1 = (float)strtol(s,NULL,10);
	s=strtok(NULL,"\n"); float speed2 = (float)strtol(s,NULL,10);
	l->speed = speed1*1000000/speed2; //recup la vitesse	
	s=strtok(NULL,"\n");
	l->total= (float)strtol(s,NULL,10); //recup la vitesse
	l->deroulement = calloc(l->total,sizeof(int));
	
	
	for(i=0;i<l->total;i++){
		s=strtok(NULL,"\n");
		l->deroulement[i] = strtol(s,NULL,10);
	}
}

void add_brique(level* m, brique* br){
  int i, j;
  for(i=br->h_brique-1;i>=0;i--){
    for(j=0;j<br->l_brique;j++){
      if(br->bloc[i][j]=='1'){
      	m->map[br->pos_x+i-1][br->pos_y+j-1].val='1';
      	m->map[br->pos_x+i-1][br->pos_y+j-1].color=br->color;
      }
    }
  }
  while(line(m));
}

bool line(level *m){ //verif si il y a une ligne complete a partir
	int i=0,j=0;
	for(i=HAUTEUR-1;i>=0;i--){
		for(j=0;j<m->largeur;j++){
			if(m->map[i][j].val=='0'){
				break;
			}else if(j == m->largeur-1 ){
				suppr(m,i);
				return true;
			}
		}
	}
	return false;
}

void suppr(level *m,int n){ //supprime la ligne n et va decaler le reste
	int i=0,j=0;
	for(i=n;i>0;i--){
		for(j=0;j<m->largeur;j++){
			m->map[i][j].val = m->map[i-1][j].val;
			m->map[i][j].color = m->map[i-1][j].color;
		}
	}
}

