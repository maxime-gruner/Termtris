#include "affichage.h"

/* Prend un descripteur de fichier en entrer, va lire la map dans le fichier et la renverra dans un tableau a 2 dimensions */
level *read_level(int fd){
  int i = 0,j = 0;
  level *m = malloc(sizeof(level));
  char buffer[BUFMAX];
  read(fd,buffer,BUFMAX); //lit les dimension
  char *s=strtok(buffer," ");
  int haut_debut = strtol(buffer,NULL,10); //convertis les dimensions en entier
  s=strtok(NULL,"\n");
  m->largeur = strtol(s,NULL,10);
  m->hauteur = HAUTEUR;
	
	//printf("'%d %d'\n",m->hauteur, m->largeur);
	
	
	m->map = malloc(m->largeur*m->hauteur);
	for(i=m->hauteur-1; i>=0; i--){
		m->map[i] = calloc(m->largeur,1);
	}
	
	/*Chargement de la map */
	for(i=m->hauteur-1; i>=0; i--){
		/*Bas de la map charge a partir du fichier */
		if(i>=HAUTEUR-haut_debut){
			s=strtok(NULL,"\n"); //lit toute la ligne de le map
		}
		for(j=0;j< m->largeur;j++){
			if(i<HAUTEUR-haut_debut ){
				m->map[i][j] = '0';
			}else{
				m->map[i][j]=s[j];
			}
		}
	}
	
	/* Chargement des briques */ 
	s=strtok(NULL,"\n");
	m->n_brique = strtol(buffer,NULL,10);
	m->brique_type = malloc(m->n_brique*sizeof(brique)); //initalisation tableau des type de brique
	s=strtok(NULL,"\0");
	//printf("%s\n",s);
	for(i=0;i<m->n_brique;i++){
		//printf("brique %i\n",i);
		m->brique_type[i] = read_brique(s); //charge les different type de brique
	
		
	}
	
	load_deroulement(m,s); //charge la vitesse et le deroulement du jeu
	
	
	return m;
}




/* affichera la map dans le terminal */
void aff_map(level *m){
	int i=0, j=0;
	for(i=0;i<m->hauteur;i++){
		for(j=0;j< m->largeur;j++){
			if(m->map[i][j]=='1'){
				write(1,"\u2588",3); //code en hexa de l unicode carre
			}else if(m->map[i][j]=='0'){
				write(1," ",1);
			}
		}write(1,"\n",1);
	}
}

void load_deroulement(level *l,char* chaine){
	char *s=NULL; int i=0;
	s=strtok(chaine," "); float speed1 = (float)strtol(s,NULL,10);
	s=strtok(NULL,"\n"); float speed2 = (float)strtol(s,NULL,10);
	l->speed = speed1/speed2; //recup la vitesse	
	s=strtok(NULL,"\n");
	//printf("%s \n",s);
	l->total= (float)strtol(s,NULL,10); //recup la vitesse
	l->deroulement = calloc(l->total,sizeof(int));
	
	
	for(i=0;i<l->total;i++){
		s=strtok(NULL,"\n");
	        //printf("i : %s \n",s);
		l->deroulement[i] = strtol(s,NULL,10);
	}
	//printf("fini \n");
}

bool touche (level* m, brique* br){
  int i,j;
  for(i=br->h_brique-1;i>=0;i--){
    for(j=0;j<br->l_brique;j++){
      if ((br->bloc[i][j]=='1') &&  (m->map[i+br->pos_x][j-1+br->pos_y] == '1')) return false;
      //else if(br->bloc[i][j]=='1' && br->pos_x+i == HAUTEUR-1 ) return false;
    }
  }
  return true;
}

void add_brique(level* m, brique* br){
  int i, j;
  for(i=br->h_brique-1;i>=0;i--){
    for(j=0;j<br->l_brique;j++){
      if(br->bloc[i][j]=='1') m->map[br->pos_x+i-1][br->pos_y+j-1]='1';
    }
  }
}
