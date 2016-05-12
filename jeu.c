#include "jeu.h"
#include <dirent.h>

bool fin_niveau = false;
/* restaure le shell en mode normal */
void restore_term(struct termios *save){
	tcsetattr(0,TCSANOW,save);
}

/* configure le shell en mode non cannonique, et save l ancienne configuration */
int set_term(struct termios *original){
	struct termios new_term;
	
	/* sauvegarde l ancien shell */
	tcgetattr(0, original);
	new_term = *original;
	cfmakeraw(&new_term); //passe le terminal en mode RAW
	
    new_term.c_oflag |= OPOST;
    
	tcsetattr(0,TCSANOW, &new_term);
	return 0;
}





/* JEU, prends le nom d'un niveau en parametre, retoune 0 si finis, 1 si quitter */
int jeu1(char *nom){
	int i=0; int nb;int ret=1; int ret2;int touch;
	fd_set rfds;
    struct timeval tv;
	
	int fd=open(nom,O_RDONLY);
	
		if(fd == -1){
			perror("erreur ouverture de fichier");
			return -1;
		}
		level *m=read_level(fd);
		close(fd);
		
	do{ //q permet de quitter sinon attendre les 17 briques
		brique tmp = m->brique_type[rand()%m->n_brique];
		int down_allowed =0; // on ne peut utiliser la descente auto qu'au bout de 2 descente
		while((touch=touche(m,&tmp))<1 || touch ==2){ //une fois en bas chngement de brique
			write(1,"\e[1;1H\e[2J",11);
			if(touch == 2){
				return 1;
			}
			
			
			aff_map(m);
			aff_brique(&tmp);
			
			tv.tv_sec = 0; //donc la brique descendra toutes les secondes
			tv.tv_usec = m->speed;
			
			while(tv.tv_sec > 0 || tv.tv_usec > 0){ //deplacement de la brique AVANT sa descente automatique, le select modife automatiquement le temps RESTANT si le timeout n est pas atteint
			
				FD_ZERO(&rfds); //reset a chaque boucle obligatoire
				FD_SET(0, &rfds);
				ret = select(1, &rfds, NULL, NULL, &tv); //attends tv seconds, ou un appuie dans ce cas on attendra encore le temps restant
				if(ret>0){ 
						ret2=input(&tmp,m); 
						if(ret2==2){ //juste pour recuperer un terminal normal si on quitte eb appuyant sur q
							
							return 1;
						}
						if(ret2==3 && down_allowed>= 2) tv.tv_usec/=10; // si on reste appuyé sur bas, on descend 10x plus vite.
						write(1,"\e[1;1H\e[2J",11);
						aff_map(m);
						aff_brique(&tmp);
				}
			}
			
				move(&tmp,1,0,m); //descente auto
				
			down_allowed ++;
		}
		
		add_brique(m,&tmp);
		i++;
	}while(!fin_niveau);
	
	
	return 0;
}

/* Lane les niveaux les uns apres les autres */
void niveaux(char ** deroulement){
	int i=0; int res=0;
	while(deroulement[i] != NULL){ //enchaine les niveau du mod
		write(1,"Niveaux ",8); // nom du niveau
		write(1,deroulement[i],strlen(deroulement[i]));
		write(1,"\n",1);
		sleep(1);
		res=jeu1(deroulement[i]);
		if(res == 1){
			write(1,"Vous avez perdu !\n",18);
			fin_niveau=true;
			return;
		}
		if(res == 0){
			write(1,"Niveau suivant !\n",17);
			fin_niveau=true;
		}
		i++;
	}
	write(1,"Vous avez fini le mode !\n",26);
}

/* Charge le deroulement du niveau et le renvoie */
char **deroulement_niveau(char *mod){
	char path[PATHSIZE]; char buffer[BUFMAX];
	int nb=0; char *niv; int i=0;
	char **deroulement;
	
	memcpy(path,mod,PATHSIZE); //copie de mod avant de la changer
	deroulement = malloc(sizeof(char*));
	
	strcat(mod,"/deroulement");
	
	int f = open(mod,O_RDONLY);
	if(f == -1){
		perror("Erreur open deroulement niveau");
		return NULL;
	}
	write(1,path,PATHSIZE);
	chdir(path); //retourne a l emplacement du mod
	chdir("niveaux"); //se place dans le rep niveaux
	
	while((nb=read(f,buffer,BUFMAX))!= 0){ //lit le fichier deroulement, et stock la succssion de niveau dans le tableau
		niv=strtok(buffer,"\n");
		do{
			deroulement[i] = malloc(sizeof(char)*PATHSIZE);
			memcpy(deroulement[i],niv,strlen(niv)); 
			i++;
		}while((niv=strtok(NULL,"\n") )!= NULL);
	}
	deroulement[i]=NULL;
	
	close(f);
	
	return deroulement;
}

/* Menu du jeu */
void menu(){ 
	char path[PATHSIZE]; int i =0; char buffer[BUFMAX]; int nb=0;
	char **deroulement_jeu;
	getcwd(path,PATHSIZE);
	
	char **choix; 
	DIR* mydir = opendir(path); 
	struct dirent *cur_dir;
	
	choix = malloc(sizeof(char*));
	write(1,"\e[18;0H",7); 
	while((cur_dir = (readdir(mydir)))){ //affiche tout les dossiers du repertoire
		if(cur_dir->d_type == DT_DIR && cur_dir->d_name[0] != '.'){ //evite les dossiers speciaux
			choix[i] = malloc(sizeof(char)*PATHSIZE);
			write(1,"\e[10C",5); 
			write(1,cur_dir->d_name,strlen(cur_dir->d_name));
			write(1,"\n\n",2);
			memcpy(choix[i],cur_dir->d_name,strlen(cur_dir->d_name));
			i++;
		}
		
	}choix[i] = NULL;
	i=0;
	
	write(1,"Entrez le numero du mode\n",26);
	do{
		nb=read(0,buffer,BUFMAX);
		if(nb == -1){
			perror("Erreur read numero mod");
			return;
		}
	}while(buffer[0]<'0' || buffer[0]>'9'); //controle la valeur entre par le joueur
	int a=strtol(buffer,NULL,10);
	
	
	deroulement_jeu = deroulement_niveau(choix[a-1]);
	i=0;
	
	niveaux(deroulement_jeu);
	
	closedir(mydir);
}





