#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define READ 0
#define WRITE 1

int main(void)
{
   int pfd[2];			/* declara o pipe */
   pipe(pfd);			/* cria o pipe */			
   if (fork() == 0) {		
      close(pfd[WRITE]);		/* fecha descriptor */
      dup2(pfd[READ], 0);		/* duplica descriptor */
      close(pfd[READ]);		/* fecha descriptor */
      execlp("wc", "wc", (char *) 0);   /* executa wc */
   } 
   else {			/* processo pai */
      close(pfd[READ]);		/* fecha descriptor */
      dup2(pfd[WRITE], 1);		/* duplica descriptor */
      close(pfd[WRITE]);		/* fecha descriptor */
      execlp("ls", "ls", (char *) 0);   /* executa ls */	
   }
   
   exit(0);
}
