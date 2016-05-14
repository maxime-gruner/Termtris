#include "reseau.h"

/* Creer le socket coté serveur, attends un client et se connecte a lui. Renvoie le socket sur lequel il communiquera avec. -1 si erreur */
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
  myaddr.sin_port = htons(65005); //port d ecoute
	
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
  write(1,"Listen...\n",10);
  int sock2 = accept(sock,(struct sockaddr*)&peer_addr,&sizeaddr);
  if(sock2 == - 1){
    perror("Fail socket 2 ");
    return -1;
  }
  write(1,"Connecter a: ",13); //affiche l ip du client qui se connect
  write(1,inet_ntoa(peer_addr.sin_addr),sizeaddr);
  write(1,"\n",1);
  return sock2;
}


/* Se connecte au serveur ip, renvoie le socket pour communiquer avec, -1 si erreur */
int connect_serv(char *ip){
  int sock = socket(AF_INET,SOCK_STREAM,0);
  if(sock == -1) perror("Erreur socket client ");	
  struct sockaddr_in myaddr;
  memset(&myaddr,0,sizeof(struct sockaddr_in));
  myaddr.sin_family = AF_INET;
  inet_pton(AF_INET,ip ,&myaddr.sin_addr.s_addr);	
  myaddr.sin_port = htons(65005); //port d ecoute
  int ret = connect(sock,(struct sockaddr*)&myaddr,sizeof(myaddr));
  if(ret == -1){
    perror("Fail connect");
    return -1;
  }
  return sock;
}

/* Ajoute la brique a la map, mais envoie un msg sur le socket si une ligne est faite */
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
  while(line(m)){ //si on fait une ligne, on envoie des donnés
  	envoi(sock,m," ");
  }
  return 0;
}

/* Envoie des donnes sur le socket. Si msg = perdu, le jeu se finit. return 1 si le jeu finit (on perd), 0 sinon */
int envoi(int sock, level *l ,char *msg ){
  if(strcmp(msg,"perdu")==0){
    write(1,"Perdu!\n",7);
    return 1;
  }
  write(sock,"1",1);
  return 0;
}

/* Surveille le socket. S'il y a des données, on lance un malus a l adversaire au hasard: vitesse augmenté ou bloc au hasard. si on lit "perdu",cela signifie que l adversaire a donc perdu et return 1. Return 0 sinon */
int recoi(int sock,level *l){
  struct pollfd fds[1]; 
  int ret=0, i=0,j=0, r=0;
  char buffer[BUFMAX]={0};
  fds[0].fd = sock; 
  fds[0].events = POLLIN;
  ret=poll(fds,1,0);
  if(ret>0){
    if(fds[0].revents & POLLIN ){ //surveille socket
      r=rand()%5;
      read(fds[0].fd,buffer,BUFMAX); //fin du jeu
      if(strcmp(buffer,"perdu")==0){
		return 1;
      }
      if(r>2){
	i = rand()%((l->hauteur-5)-10)+10; //tire un nombre entre 10 et l->hauteur-2
	j =	rand()%(l->largeur-1);
	l->map[i][j].val ='1';
      }else l->speed = l->speed/5;
    }
  }
  return 0;
}

/* Mode de jeu en reseau. Permet de lancer soit le serveur sooit le client. */
void mode_reseau(){
  int sock,res=0, nb=0;
  char buffer[BUFMAX];
  write(1,"Serveur ou client ?\n",20);
  write(1,"1 Serveur \n2 Client\n",20);
  do{
    nb=read(0,buffer,BUFMAX);
    if(nb == -1){
      perror("Erreur read numero mod");
      return;
    }
  }while(buffer[0]<'1' || buffer[0]>'2' ); //controle la valeur entre par le joueur
  
  if(buffer[0] == '1'){  // si serveur, creer un serveur
    if((sock=creer_serveur() ) == -1) write(1,"Echec creation serveur\n",23); //creer le serveur
  }
    else{
      int nb_total=0;
      write(1,"Precisez l'ip du servuer: ",25); //ip reseau local ou machine local
      do{
	nb=read(0,(buffer+nb_total),BUFMAX); //aucun echo mais ça ecrit
	nb_total++; 
	if(nb == -1){
	  perror("Erreur ip");
	  return;
	}
      }while(buffer[nb_total-1] != 13); buffer[nb_total-1]='\0'; //la saisie de l ip fini quand on appuis sur entrée
      write(1,buffer,nb_total-1);
      write(1,"\n",1);
      sock=connect_serv(buffer); //se connecte au serveur dont l ip a ete saisie precedement
      if(sock == -1){
	write(1,"Connection echoue\n",18);
	return;
      }
    }
  res=jeu_reseau(sock,"mod3_reseau/niveaux/1"); //il n y a qu une map infini
  write(1,"\e[1;1H\e[2J",11);
  if(res == 1){
    write(1,"Vous avez perdu !\n",18);
    return;
  }else{
    write(1,"Gagnez !\n",9);
  }
  shutdown(sock,2); //ferme le socket
}
