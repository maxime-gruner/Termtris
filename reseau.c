#include "reseau.h"


int creer_serveur(){
	int ret=0;
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock == -1){
		perror("Fail socket ");
		return-1;
	}struct sockaddr_in myaddr,peer_addr;
	memset(&myaddr,0,sizeof(struct sockaddr_in));
	
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = INADDR_ANY;
	myaddr.sin_port = htons(65005);
	
	socklen_t sizeaddr = sizeof(peer_addr);
	
	
	ret = bind(sock,(struct sockaddr*) &myaddr,sizeof(myaddr) );
	if(ret == -1){
		perror("Fail bind ");
		return -1;
	}
	write(1,"En attente de connection \n",26);
	ret = listen(sock,5);
	if(ret == -1){
		perror("Fail listen ");
		return -1;
	}
	
	int sock2 = accept(sock,(struct sockaddr*)&peer_addr,&sizeaddr);
	if(sock2 == - 1){
		perror("Fail socket 2 ");
		return -1;
	}
	
	write(1,"Connecter a: ",13);
	write(1,inet_ntoa(peer_addr.sin_addr),sizeaddr);
	write(1,"\n",1);
	return sock2;
}



int connect_serv(char *ip){
	
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock == -1) {
		perror("Erreur socket client ");
	}
	
	struct sockaddr_in myaddr;
	memset(&myaddr,0,sizeof(struct sockaddr_in));
	
	
	myaddr.sin_family = AF_INET;
	inet_pton(AF_INET,ip ,&myaddr.sin_addr.s_addr);	
	myaddr.sin_port = htons(65005);
	
	int ret = connect(sock,(struct sockaddr*)&myaddr,sizeof(myaddr));
	if(ret == -1){
		perror("Fail connect");
		return -1;
		
	}
	return sock;
}

int add_brique_reseau(level* m, brique* br,int sock){
  int i, j;
  for(i=br->h_brique-1;i>=0;i--){
    for(j=0;j<br->l_brique;j++){
      if(br->bloc[i][j]=='1'){
      	m->map[br->pos_x+i-1][br->pos_y+j-1].val='1';
      	m->map[br->pos_x+i-1][br->pos_y+j-1].color=br->color;
      }
    }
  }
  while(line(m)){
  	envoi(sock,m);
  	break;
  }
  return 0;
}

int envoi(int sock, level *l,char  ){
	
	write(sock,"1",1);
	
	return 0;
}

void recoi(int sock,level *l){
	struct pollfd fds[1]; int ret=0; int i=0,j=0;
	char buffer[BUFMAX];
	fds[0].fd = sock; 
	fds[0].events = POLLIN;
	ret=poll(fds,1,0);
	if(ret>0){
		if(fds[0].revents & POLLIN ){
			read(fds[0].fd,buffer,BUFMAX); //sert a rien mais obliger de lire
			i = rand()%l->hauteur;
			j =	rand()%l->largeur;
			l->map[i][j].val ='1';
		}
	}
}


void mode_reseau(){
	int sock;
	int nb=0; char buffer[BUFMAX];
	write(1,"Serveur ou client ?\n",20);
	write(1,"1 Serveur \n2 Client\n",20);
	
	do{
		nb=read(0,buffer,BUFMAX);
		if(nb == -1){
			perror("Erreur read numero mod");
			return;
		}
	}while(buffer[0]<'1' || buffer[0]>'2' ); //controle la valeur entre par le joueur
	
	if(buffer[0] == '1'){ // si serveur, creer un serveur
		if((sock=creer_serveur() ) == -1){
			write(1,"Echec creation serveur\n",23);
		}
		
		
	}else{
		int nb_total=0;
		write(1,"Precisez l'ip du servuer: ",25);
		do{
			nb=read(0,(buffer+nb_total),BUFMAX); nb_total++; 
			if(nb == -1){
				perror("Erreur ip");
				return;
			}
		}while(buffer[nb_total-1] != 13); 
			write(1,buffer,nb_total-1);
			write(1,"\n",1);
		sock=connect_serv(buffer);
	}
	
	jeu_reseau(sock,"mod2/niveaux/1");
	shutdown(sock,2);
}