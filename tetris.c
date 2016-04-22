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
    
	tcsetattr(0,TCSAFLUSH, &new_term);
	return 0;
}




int main (int argc, char *argv[]){
	int i=0; int nb;int ret;
	write(1,"\e[1;1H\e[2J",11); //place le curseur en haut a gauche, et clear le terminal
	struct termios save_term;
	set_term(&save_term);
	
	struct pollfd pollfds[1];
	pollfds[0].fd = 1;
	pollfds[0].events = POLLIN;
	
	write(1,"\x1b[?25l",6); //cache le curseur
	char c;
	int fd=open("mod1/niveaux/1",O_RDONLY);
	
		if(fd == -1){
			perror("erreur ouverture de fichier");
		}
		level *m=read_level(fd);
		
		
	do{
		nb=m->deroulement[i];
		brique tmp = m->brique_type[nb-1];
		
		while(1){
			//poll(NULL,0,1000);
			ret = poll(pollfds,1,1000);
				if(ret >0){
					input(&tmp);
					
			}
				move(&tmp,1,0); //descente auto
			write(1,"\e[1;1H\e[2J",11);
			aff_map(m);
			aff_brique(&tmp);
			
		} 
		
		
		//c=getchar();
		//i++;
	}while(i<m->total);
	
	restore_term(&save_term);
	
	write(1,"\x1b[?25h",6); //remet le curseur
	close(fd);
	return 0;
}
