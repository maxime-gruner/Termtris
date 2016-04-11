#include "affichage.h"
#include "brique.h"

/* restaure le shell en mode normal */
void restore_term(struct termios *save){
	tcsetattr(0,TCSANOW,save);
}

/* configure le shell en mode non cannonique, et save l ancienne configuration */
int set_term(struct termios *original){
	struct termios new_term;
	write(1,"\e[1;1H\e[2J",11); //place le curseur en haut a gauche, et clear le terminal
	/* sauvegarde l ancien shell */
	tcgetattr(0, original);
	
	cfmakeraw(&new_term); //passe le terminal en mode RAW
	new_term.c_oflag |= OPOST; //sinon le terminal gere mal les \n
	tcsetattr(0,TCSANOW, &new_term);
	return 0;
}




int main (int argc, char *argv[]){
	//int i=0;
	struct termios save_term;
	set_term(&save_term);
	
	write(1,"\x1b[?25l",6); //cache le curseur
	char c;
	int fd=open("mod1/niveaux/1",O_RDONLY);
		if(fd == -1){
			perror("erreur ouverture de fichier");
		}
		level *m=read_level(fd);
		aff_map(m);
		
	do{
		aff_brique(&m->brique_type[0]);
		c=getchar();
		//i++;
	}while(c!='q');
	restore_term(&save_term);
	
	write(1,"\x1b[?25h",6); //remet le curseur
	close(fd);
	return 0;
}
