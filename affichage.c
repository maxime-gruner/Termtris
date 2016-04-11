#include "affichage.h"

/* Prend un descripteur de fichier en entrer, va lire la map dans le fichier et la renverra dans un tableau a 2 dimensions */
level *read_level(int fd){
	int i = 0,j = 0;int ret=0;
	int n_brique=0;
	level *m = malloc(sizeof(level));
	
	char buffer[64];
	
	read(fd,buffer,5); //lit les dimension
	
	char *s=strpbrk(buffer," ");
	*s='\0';*(s+3)='\0';
	int haut_debut = strtol(buffer,NULL,10); //convertis les dimensions en entier
	m->largeur = strtol(buffer+2,NULL,10);
	
	m->hauteur = HAUTEUR;
	
	//printf("'%d %d'\n",m->hauteur, m->largeur);
	
	
	m->map = malloc(sizeof(char*)*m->hauteur);
	for(i=0;i<m->hauteur; i++){
		m->map[i] = calloc(m->largeur,sizeof(char));
	}
	
	/*Chargement de la map */
	for(i=0;i< m->hauteur;i++){
		/*Bas de la map charge a partir du fichier */
		if(i>= m->hauteur-haut_debut){
			ret=read(fd,buffer,m->largeur); //lit toute la ligne de le map
			lseek(fd,1,SEEK_CUR);
				if(ret == -1 ){
					perror("Erreur de lecture du niveau");
					return NULL;
				}
		}
		for(j=0;j< m->largeur;j++){
			if(i< m->hauteur-haut_debut ){
				m->map[i][j] = '0';
			}else{
				if(buffer[j]=='1' ){
					m->map[i][j]='1'; //mur
				}else if(buffer[j] =='0'){
					m->map[i][j] = '0'; //rien
				}
			}
		}
	}
	
	/* Chargement des briques */ 
	ret = read(fd,buffer,2); buffer[ret-1]='\0';
	n_brique=strtol(buffer,NULL,10);
	m->n_brique = n_brique;
	m->brique_type = malloc(n_brique*sizeof(brique)); //initalisation tableau des type de brique
	
	
	for(i=0;i<n_brique;i++){
		m->brique_type[i] = read_brique(fd);
		
	}
	
	
	return m;
}




/* affichera la map dans le terminal */
void aff_map(level *m){
	int i=0, j=0;
	for(i=0;i< m->hauteur;i++){
		for(j=0;j< m->largeur;j++){
		//write(1,&m->map[i][j],1);
			if(m->map[i][j]=='1')
				write(1,"@",1);
			else if(m->map[i][j]=='0'){
				write(1," ",1);
			}else
				printf("WTF %d %d %d\n",i,j,m->map[i][j]);
		}write(1,"\n",1);
	}
}




