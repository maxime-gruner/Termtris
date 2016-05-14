#include "affichage.h"
#include "brique.h"
#include "jeu.h"
#include "reseau.h"




int main (int argc, char *argv[]){
  char buffer[BUFMAX];
  int nb=0; 
  write(1,"\x1b[?25l",6); //cache le curseur
  write(1,"\e[1;1H\e[2J",11); //place le curseur en haut a gauche, et clear le terminal
  struct termios save_term;
  set_term(&save_term);
  
  write(1,"Selection du mode \n",19);
  write(1,"1 Normal \n2 Multi\n",18);
  do{
    nb=read(0,buffer,BUFMAX);
    if(nb == -1){
      perror("Erreur read numero mod");
      return -1;
    }
  }while(buffer[0]<'1' || buffer[0]>'2' ); //controle la valeur entre par le joueur
	
  if(buffer[0] == '1') menu();
  else mode_reseau();	
	
  restore_term(&save_term);
  write(1,"\x1b[?25h",6); //remet le curseur
  return 0;
}
