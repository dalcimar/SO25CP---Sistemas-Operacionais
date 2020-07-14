#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

//Processo filho envia dados para o processo pai

int main() {
   int n, fd[2];
   pid_t pid;
   if (pipe(fd)<0) { 
      fprintf(stderr,"Erro no tubo\n");
      _exit(1); 
   }
   if ((pid=fork())<0) {
      fprintf(stderr,"Erro no fork\n");
      _exit(1);
   }

   if ( pid>0 ) { /* processo pai */
      #define MAX 128
      char line[MAX];
      close(fd[WRITE]);
      n = read(fd[READ],line,MAX);
      write(WRITE, &line[0], n);
      close(fd[READ]);
      _exit(0); 
   } 
   else if ( pid==0 ) { /* processo filho */
      #define LEN 8
      char msg[LEN]={'B','o','m',' ','d','i','a','\n'};
      close(fd[READ]);
      write(fd[WRITE], &msg[0], LEN);
      close(fd[WRITE]);
   }
}

