// Para rodar o programa: $testa_wait_6 <número de processos> 
// Cada filho criado espera por seu próprio filho completar antes de imprimir a msg. 
// As mensagens aparecem na ordem reversa da criação. 
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main (int argc, char *argv[]) {
    pid_t childpid; 
    int i, n;
    
    if (argc != 2){   /* check for number of command-line arguments */ 
        fprintf(stderr, "Usage: %s processes\n", argv[0]);
        return 1; 
    }  
      
    n = atoi(argv[1]);  
    for (i = 1; i < n; i++)
        if ((childpid = fork()) > 0) //apenas pai entra
            break;
    
    for (;;) {
        childpid = wait(NULL);
        if ((childpid == -1) && (errno != EINTR)){
            fprintf(stderr, "Brekar : I am process %ld, my parent is %ld\n", (long)getpid(),(long)getppid());
            break;
        }
    }
    fprintf(stderr, "I am process %ld, my parent is %ld\n", (long)getpid(),(long)getppid());
    return 0; 
}

