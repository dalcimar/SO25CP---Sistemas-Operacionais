#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void SIGUSR1_handler(){
	printf("Restaurando ação default do  SIGUSR1.\n");
	signal(SIGTSTP, SIG_DFL);
}

void SIGINT_handler(){
	printf("Tratando CTRL+C.\n");
}
     
int main(void){
	signal(SIGUSR1, SIGUSR1_handler);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, SIGINT_handler);

	for(;;){
		pid_t pid=getpid();
		printf("pid=%ld\n", (long)pid);
		sleep(1);
	}
}
