#include "affichage.h"
#include "brique.h"
#include <poll.h>

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




int main (int argc, char *argv[]){
	int i=0; int nb;int ret; int ret2;
	write(1,"\e[1;1H\e[2J",11); //place le curseur en haut a gauche, et clear le terminal
	struct termios save_term;
	set_term(&save_term);
	
	fd_set rfds;
    struct timeval tv;
	
	write(1,"\x1b[?25l",6); //cache le curseur
	int fd=open("mod1/niveaux/1",O_RDONLY);
	
		if(fd == -1){
			perror("erreur ouverture de fichier");
		}
		level *m=read_level(fd);
		close(fd);
		
	do{ //q permet de quitter sinon attendre les 17 briques
		nb=m->deroulement[i];
		brique tmp = m->brique_type[nb-1];
		
		while(touche(m,&tmp)){ //une fois en bas chngement de brique, mieux gerer quand les collisions seront faites
			write(1,"\e[1;1H\e[2J",11);
			aff_map(m);
			aff_brique(&tmp);
			
			tv.tv_sec = 0; //donc la brique descendra toutes les secondes
			tv.tv_usec = 200000;
			
			while(tv.tv_sec > 0 || tv.tv_usec > 0){ //deplacement de la brique AVANT sa descente automatique, le select modife automatiquement le temps RESTANT si le timeout n est pas atteint
			
				FD_ZERO(&rfds); //reset a chaque boucle obligatoire
				FD_SET(0, &rfds);
				ret = select(1, &rfds, NULL, NULL, &tv); //attends tv seconds, ou un appuie dans ce cas on attendra encore le temps restant
				if(ret>0){ 
						ret2=input(&tmp); 
						if(ret2==2){ //juste pour recuperer un terminal normal si on quitte eb appuyant sur q
							restore_term(&save_term);
							write(1,"\x1b[?25h",6); //remet le curseur
							return 0;
						}
						write(1,"\e[1;1H\e[2J",11);
						aff_map(m);
						aff_brique(&tmp);
				}
			}
			
				move(&tmp,1,0); //descente auto
				
				
			}
		add_brique(m,&tmp);
		i++;
	}while(i<m->total);
	
	restore_term(&save_term);
	
	write(1,"\x1b[?25h",6); //remet le curseur
	return 0;
}
