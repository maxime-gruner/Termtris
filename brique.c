#include "brique.h"


brique read_brique(char *chaine){
  
                printf("je suis là\n");
	int i=0, j=0;
	brique br;
	char *s;
	s=strtok(chaine," ");
	br.h_brique = strtol(s,NULL,10);
	s=strtok(NULL,"\n");
	br.l_brique = strtol(s,NULL,10); 
		br.pos_x = 1; //pos initiale de spawn
		br.pos_y = 20; 	
		  br.bloc = malloc(1*br.h_brique); 
			for(i=0;i<br.h_brique;i++){
				br.bloc[i] = calloc(br.l_brique,sizeof(char));
					s=strtok(NULL,"\n"); 
	printf("%s ok\n",s);
				for(j=0;j<br.l_brique;j++){
					br.bloc[i][j]=s[i];
			}
		}
		
	s=strtok(NULL,"\0");
	strcpy(chaine,s);
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