#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t pid; 
    
    pid = fork();
    if(pid==0){
    	sleep(2);
    	printf("sou filho 1, estou terminando\n");
    	exit(0);
    }
    
    waitpid(-1, NULL, 0);
    printf("sou pai, estou terminando\n");
    exit(0);     
}
