#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	pid_t pid; 

	pid = fork();
	if(pid==0){
		execl("jovemgafanhotoshell","jovemgafanhotoshell", NULL); // troca o código binário, pelo binário do date
		perror("Erro: ");
	}

	waitpid(pid, NULL, 0);
	printf("sou pai, estou terminando\n");
	exit(0);     
}
