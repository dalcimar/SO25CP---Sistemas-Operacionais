#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define ever ;;

int main(){
	pid_t pid, childpid;
	int status;

	pid = fork();
	if(pid==0){
		printf("sou filho 1, estou em looping process ID:%ld  parent ID:%ld\n", (long)getpid(), (long)getppid());
		sleep(2);
		printf("sou filho 1, estou em looping process ID:%ld  parent ID:%ld\n", (long)getpid(), (long)getppid());
		for(ever);
	}

	printf("sou pai, estou terminando\n");
}  
