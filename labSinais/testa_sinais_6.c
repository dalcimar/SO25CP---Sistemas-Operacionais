#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>

void morte_filho(int n){
    printf("morreu o meu filho %d eu sou %d\n", wait(NULL), getpid());
}

int main() {
    signal(SIGCHLD, morte_filho);
    //signal(SIGCHLD, SIG_DFL);
    //signal(SIGCHLD, SIG_IGN);
    pid_t pid=fork();
    if (pid==0) {
        if(fork() == 0){
            printf("neto.....\n");
            sleep(1);
            exit(0);
        }else{
            printf("FILHO...\n");
            exit(0);
        }
    }
    else {
        while(1);
        exit(0); 
    }
}
