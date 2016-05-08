#include "brique.h"


brique read_brique(char *chaine, int c){
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
		  br.bloc = malloc(sizeof(char*)*br.h_brique); 
			for(i=0;i<br.h_brique;i++){
				br.bloc[i] = calloc(br.l_brique,sizeof(char));
					s=strtok(NULL,"\n"); 
				for(j=0;j<br.l_brique;j++){
						br.bloc[i][j]=s[j];
			}
		}
	br.color=c%9+1;
	s=strtok(NULL,"\0");
	strcpy(chaine,s);
	
	//aff_brique(&br);
		return br;
}



void aff_brique(brique *b){
	char buffer[32];
	int i=0,j=0;
	int x=b->pos_x, y=b->pos_y;
	printf("\nl brique '%d' h brique '%d' pos x '%d pos y '%d'\n",b->l_brique,b->h_brique,b->pos_x,b->pos_y);
	for(i=0;i< b->h_brique;i++){
		for(j=0;j< b->l_brique;j++){
		
			sprintf(buffer,"\e[%d;%dH",x+i,y+j);
			write(1,buffer,strlen(buffer));
			
			if(b->bloc[i][j] == '1'){
				switch(b->color){
				  case 1: write(1,"\033[31m\u2588\033[0m",12); break;
				  case 2: write(1,"\033[32m\u2588\033[0m",12); break;
				  case 3: write(1,"\033[33m\u2588\033[0m",12); break;
				  case 4: write(1,"\033[34m\u2588\033[0m",12); break;
				  case 5: write(1,"\033[35m\u2588\033[0m",12); break;
				  case 6: write(1,"\033[36m\u2588\033[0m",12); break;
				  case 7: write(1,"\033[37m\u2588\033[0m",12); break;
				  case 8: write(1,"\033[38m\u2588\033[0m",12); break;
				  case 9: write(1,"\033[39m\u2588\033[0m",12); break;
				}
			}else if(b->bloc[i][j]=='0'){
				write(1," ",1);
			}
		}write(1,"\n",1);
	}
}



int input(brique *b, level* m){ //gere les touche appuyer
	char buffer[8];
	read(0,buffer,8);
	
	if(buffer[0] == 27){
		if(buffer[1] == 91){
			if(buffer[2]=='C'){ //droite
				move(b,0,1,m);
			}else if(buffer[2]=='D'){ //gauche
				move(b,0,-1,m);
			}
		}
	}else if(buffer[0] == 'q'){
		return 2;
	}else if(buffer[0] == ' '){
		rotate(m,b);
	}
	
	return 0;
	
}

void move(brique *br,int x,int y,level* m){ //mouvement
  int i,j;
  bool possible = true;
  for(i=br->h_brique-1;i>=0;i--){
    for(j=0;j<br->l_brique;j++){
      if ((br->bloc[i][j]=='1') &&  ((m->map[i+br->pos_x][j+y-1+br->pos_y].val == '1') || (j+y-1+br->pos_y)<0 || (j+y-1+br->pos_y)>m->largeur-1)) possible=false;
    }
  }
  if(possible) br->pos_y =br->pos_y+y;
  br->pos_x =br->pos_x+x;
}

void rotate(level *m,brique *b){ //tourne la brique
	
	int i=0,j=0,h=0,l=b->h_brique-1;
	int tmp;
	char tab[b->l_brique][b->h_brique];
	
	if( b->pos_y +b->h_brique - m->largeur-1> 0 ) return;
	for(i=0;i<b->l_brique;i++){
		if(m->map[b->pos_x+i][b->pos_y].val == '1')
			return;
	}
	
	for(i=0;i<b->h_brique;i++){
		for(j=0;j<b->l_brique;j++){
			tab[h][l] = b->bloc[i][j];
			h++;
		}l--;h=0;
	}
	
	tmp = b->h_brique;
	b->h_brique = b->l_brique ;
	b->l_brique = tmp; 
	
	
	b->bloc= malloc(sizeof(char*)*b->h_brique);
	for(i=0;i<b->h_brique;i++){
		b->bloc[i] = calloc(sizeof(char),b->l_brique);
		memmove(b->bloc[i],tab[i],b->l_brique);
	}
	
}


