#include "brique.h"


brique read_brique(int fd){
	int ret=0, i=0, j=0;
	char *s=NULL;char buffer[64];
	brique br;
	ret = read(fd,buffer,4); buffer[ret-1] = '\0' ; //lit la taille de la brique_type
		s=strpbrk(buffer," "); *s='\0'; //separe les deux dimension
		br.h_brique = strtol(buffer,NULL,10);
		br.l_brique = strtol(buffer+2,NULL,10); 
		
		br.pos_x = 1; //pos initiale de spawn
		br.pos_y = 20; 
		
		
		br.bloc = malloc(sizeof(char)*br.h_brique); 
			for(i=0;i<br.h_brique;i++){
				br.bloc[i] = calloc(br.l_brique,sizeof(char)); 
				for(j=0;j<br.l_brique+1;j++){
					ret = read(fd,buffer,1);
					if(buffer[0] == '1'){
						br.bloc[i][j] = '1';
					}else if(buffer[0] == '0'){
						br.bloc[i][j] = '0';
					}
			}
		}
		
		
		return br;
}


void aff_brique(brique *b){
	char buffer[32];
	int i=0,j=0;
	int x=b->pos_x, y=b->pos_y;
	
	for(i=0;i< b->h_brique;i++){
		for(j=0;j< b->l_brique;j++){
		
			sprintf(buffer,"\e[%d;%dH",x+i,y+j);
			write(1,buffer,strlen(buffer));
			
			if(b->bloc[i][j] == '1'){
				write(1,"@",1);
			}else
				write(1," ",1);
			
		}write(1,"\n",1);
	}
}

