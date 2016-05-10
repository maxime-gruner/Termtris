
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "brique.h"

int main (){
  char s[50];
  read(0,s,50);
  printf("%s \n",s);
  return 0;
}