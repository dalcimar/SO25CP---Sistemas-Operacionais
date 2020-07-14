#include <stdio.h>
#include <string.h>
#include <sys/file.h>
#include <sys/types.h>
//#include "defs.h"
#define LEN 100
#define FNAME "testFIFO"

int readChar(int fd, char *buf) {
   int n;
   do n=read(fd,buf,1);
   while (n>0 && *buf++!='\0');
   return n>0; 
}

main() {
   int fd;
   char str[LEN];
   mkfifo(FNAME,0660);
   fd=open(FNAME,O_RDONLY);
   if (fd<0) { printf("Erro na abertura da fila\n"); exit(1); }
   while (readChar(fd,str)) printf("%s",str);
   close(fd); 
}
