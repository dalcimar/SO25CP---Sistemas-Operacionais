// Para rodar o programa: $testa_wait_3 <número de processos>
// Pai espera por todos os filhos
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main (int argc, char *argv[]) {
    pid_t childpid = 0;
    int i, n;
    
    if (argc != 2) { // check number of command-line arguments
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return 1;
    }
    
    n = atoi(argv[1]);
    for (i = 1; i < n; i++)
        if ((childpid = fork()) <= 0) //only the child (or error) enters
            break;
    
    for (;;) {
        childpid = wait(NULL);
        if ((childpid ==-1) && (errno != EINTR)){
            fprintf(stderr, "Break: I am process %ld, my parent is %ld\n", (long)getpid(), (long)getppid());
            break;
        }
    }
    
    fprintf(stderr, "I am process %ld, my parent is %ld\n", (long)getpid(), (long)getppid());
    return 0;
}
