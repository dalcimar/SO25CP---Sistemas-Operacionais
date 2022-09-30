#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main () {
    pid_t pid1, pid2;
    int status;
    
    pid1 = fork();
    if(pid1==0){
    	sleep(2);
    	printf("sou filho 1, estou terminando\n");
    	exit(0);
    }
    
    pid2 = fork();
    if(pid2==0){
    	printf("sou filho 2, estou terminando\n");
    	exit(0);
    }
    
    //waitpid(-1, NULL, 0);
    waitpid(pid2, NULL, 0);
    waitpid(pid1, NULL, 0);
    printf("sou pai, estou terminando\n");
    exit(0);     
}
