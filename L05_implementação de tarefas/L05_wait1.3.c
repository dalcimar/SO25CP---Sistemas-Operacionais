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
		sleep(2);
		printf("sou filho 1, estou terminando\n");
		exit(0);
	}

	printf("sou pai, estou entrando em looping infinito\n");
	printf("meu filho irá virar zumbi pois não dou atenção a ele\n");
	for(ever);  
}  
