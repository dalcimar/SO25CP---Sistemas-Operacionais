#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	pid_t pid, childpid;
	int status;

	pid = fork();
	if(pid==0){
		sleep(2);
		printf("sou filho 1, estou terminando\n");
		//exit(7); // termino normal com informação 7
		//abort(); // termino anormal com geração de sinal SIGABRT 6
		//int a = 1/0; // termino anormal com geração de sinal SIGFPE 8
		kill(getpid(),SIGSTOP);
	}

	childpid = waitpid(-1, &status, 0); // adicionar WUNTRACED | WCONTINUED como opção para fazer com que wait desbloquei caso processo filho mude de estado
	
	if (childpid == -1)
		perror("Failed to wait for child");
	else if (WIFEXITED(status))
		printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		printf("abnormal termination, signal number = %d\n", WTERMSIG(status));
	else if (WIFSTOPPED(status))
		printf("child stopped, signal number = %d\n", WSTOPSIG(status));
	
	printf("sou pai, estou terminando\n");
	exit(0);     
}  
