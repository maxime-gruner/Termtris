#include "brique.h"


brique read_brique(char *chaine){
	int i=0, j=0;
	brique br;
	char *s;
	s=strtok(chaine," ");
	br.h_brique = strtol(s,NULL,10);
	s=strtok(NULL,"\n");
	br.l_brique = strtol(s,NULL,10); 
	//printf("dim '%s'\n",s);
		br.pos_x = 1; //pos initiale de spawn
		br.pos_y = 20; 	
		  br.bloc = malloc(1*br.h_brique); 
			for(i=0;i<br.h_brique;i++){
				br.bloc[i] = calloc(br.l_brique,sizeof(char));
					s=strtok(NULL,"\n"); 
				for(j=0;j<br.l_brique;j++){
						br.bloc[i][j]=s[j];
			}
		}
		
	s=strtok(NULL,"\0");
	strcpy(chaine,s);
	
	//aff_brique(&br);
		return br;
}



void aff_brique(brique *b){
	char buffer[32];
	int i=0,j=0;
	int x=b->pos_x, y=b->pos_y;
	printf("l brique '%d' h brique '%d'\n",b->l_brique,b->h_brique);
	for(i=0;i< b->h_brique;i++){
		for(j=0;j< b->l_brique;j++){
		
			sprintf(buffer,"\e[%d;%dH",x+i,y+j);
			write(1,buffer,strlen(buffer));
			
			if(b->bloc[i][j] == '1'){
				write(1,"\u2588",3);
			}else if(b->bloc[i][j]=='0'){
				write(1," ",1);
			}
		}write(1,"\n",1);
	}
}



int input(brique *b){ //gere les touche appuyer
	char buffer[8];
	int r=read(0,buffer,8);
	if(buffer[0] == 27){
		if(buffer[1] == 91){
			if(buffer[2]=='C'){ //droite
				move(b,0,1);
			}else if(buffer[2]=='D'){ //gauche
				move(b,0,-1);
			}
		}
	}else if(buffer[0] == 'q'){
		return 2;
	}else if(buffer[0] == ' '){
		rotate(b);
	}
	
	return 0;
	
}

void move(brique *b,int x,int y){ //mouvement
	b->pos_x =b->pos_x+x;
	b->pos_y =b->pos_y+y;
}

void rotate(brique *b){ //tourne la brique
	
	int i=0,j=0,h=0,l=b->h_brique-1;
	//char tab[b->h_brique][b->l_brique];
	brique *bck= malloc(sizeof(brique));
	bck->h_brique = b->l_brique;
	bck->l_brique = b->h_brique;
	bck->pos_x = b->pos_x;
	bck->pos_y = b->pos_y;
	
	bck->bloc = malloc(sizeof(char)*bck->h_brique);
	for(i=0;i<bck->h_brique;i++){
		bck->bloc[i] = malloc(sizeof(char)*bck->l_brique);
	}
	
	for(i=0;i<b->h_brique;i++){
		for(j=0;j<b->l_brique;j++){
			bck->bloc[h][l] = b->bloc[i][j];
			h++;
		}l--;h=0;
	}
	
	
	memcpy(b,bck,sizeof(brique));
	
}


