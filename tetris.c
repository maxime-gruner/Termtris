#include "affichage.h"
#include "brique.h"
#include "jeu.h"

#include <poll.h>




int main (int argc, char *argv[]){
	
	
	write(1,"\x1b[?25l",6); //cache le curseur
	write(1,"\e[1;1H\e[2J",11); //place le curseur en haut a gauche, et clear le terminal
	struct termios save_term;
	set_term(&save_term);
	
	menu();
	
	
	restore_term(&save_term);
	
	write(1,"\x1b[?25h",6); //remet le curseur
	
	return 0;
}
