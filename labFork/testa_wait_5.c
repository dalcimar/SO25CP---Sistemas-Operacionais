/* Determina o status de exit de um processo filho - TEM ERRO - FALTA ACERTAR!! */
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void) {
   pid_t pid,childpid;
   int status;

   pid = fork();
   if (pid == 0){
      exit(7); /* child1 finishes normally */
      //abort();
      //int a = 1/0;
      //sleep(5);
   }
   else if (pid > 0){
    childpid = wait(&status);
    if (childpid == -1)
        perror("Failed to wait for child");
    else if (WIFEXITED(status))
        printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("abnormal termination, signal number = %d%s\n", WTERMSIG(status));
    else if (WIFSTOPPED(status))
        printf("child stopped, signal number = %d\n", WSTOPSIG(status));
   }
   
   return 0;
}
   
