#include "affichage.h"

/* Prend un descripteur de fichier en entrer, va lire la map dans le fichier et la renverra dans un tableau a 2 dimensions */
map *read_map(int fd){
	int i = 0,j = 0;
	map *m = malloc(sizeof(map));
	
	char buffer[128];
	read(fd,buffer,5); //lit les dimension
	char *s=strpbrk(buffer," ");
	*s='\0';
	m->hauteur = strtol(buffer,NULL,10); //convertis les dimensions en entier
	m->largeur = strtol(buffer+2,NULL,10);
	
	m->matrice = malloc(sizeof(char*)*m->hauteur);
	for(i=0;i< m->hauteur;i++){
		int ret=read(fd,buffer,m->largeur+1); //lit toute la ligne de le map
		if(ret == -1 ){
			perror("Erreur de lecture du niveau");
		}
		m->matrice[i]=malloc(sizeof(char)*(m->largeur+1));
		for(j=0;j<= m->largeur;j++){
			if(buffer[j]=='1' ){
				m->matrice[i][j]='1'; //mur
			}else if(buffer[j] == 0 && buffer[j] != '\n'){
				
				m->matrice[i][j] = '0'; //rien
			}
			
		}
	}
	return m;
}

/* affichera la map dans le terminal */
void aff_map(map *m){
	int i=0, j=0;
	for(i=0;i< m->hauteur;i++){
		for(j=0;j< m->largeur;j++){
			if(m->matrice[i][j]=='1')
				write(1,"*",1);
			else{
				write(1," ",1);
			}
		}write(1,"\n",1);
	}
}




