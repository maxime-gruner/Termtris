#include "brique.h"


brique read_brique(int fd){
	int ret=0, i=0, j=0;
	char *s=NULL;char buffer[64];
	brique br;
	ret = read(fd,buffer,4); buffer[ret-1] = '\0' ; //lit la taille de la brique_type
		s=strpbrk(buffer," "); *s='\0'; //separe les deux dimension
		br.h_brique = strtol(buffer,NULL,10);
		br.l_brique = strtol(buffer+2,NULL,10); 
		
		br.bloc = malloc(sizeof(char)*br.h_brique); 
			for(i=0;i<br.h_brique;i++){
				br.bloc[i] = calloc(br.h_brique,sizeof(char)); 
				for(j=0;j<br.l_brique+1;j++){
					ret = read(fd,buffer,1);
					if(buffer[0] != '\n'){
						br.bloc[i][j] = buffer[0];
					}
			}
		}
		
		
		return br;
}


void aff_brique(brique *b){
	int i=0,j=0;
	for(i=0;i< b->h_brique;i++){
		for(j=0;j< b->l_brique;j++){
			
			write(1,&b->bloc[i][j],1);
		}printf("\n");
	}
}

