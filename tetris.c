#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

/* restaure le shell en mode normal */
void restore_term(struct termios *save){
	tcsetattr(0,TCSANOW,save);
}

/* configure le shelle en mode non cannonique, et save l ancienne configuration */
int set_term(struct termios *original){
	struct termios new_term;
	write(1,"\e[1;1H\e[2J",11); //place le curseur en haut a gauche, et clear le terminal
	/* sauvegarde l ancien shell */
	tcgetattr(0, original);
	
	cfmakeraw(&new_term); //passe le terminal en mode RAW
	tcsetattr(0,TCSAFLUSH, &new_term);
	return 0;
}




int main (int argc, char *argv[])
{
	
	struct termios save_term;
	set_term(&save_term);
	char c;
	do{
		//printf("test");
		c=getchar();
		printf("%c",c);
	}while(c!='q');
	restore_term(&save_term);
	return 0;
}
