#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	pid_t pid; 

	pid = fork();
	if(pid==0){
		sleep(3);
		printf("sou filho, vou trocar meu código\n");
		//execl("/bin/date","date", NULL); // troca o código binário, pelo binário do date
		execl("soma","soma",NULL);
		printf("esse print não será mostrado\n"); // não irá executar, pois o exec troca o código fonte
	}

	//waitpid(pid, NULL, 0);
	printf("sou pai, estou terminando\n");
	exit(0);     
}
