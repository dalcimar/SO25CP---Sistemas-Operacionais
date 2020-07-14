#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void SIGINT_handler(){
	printf("Tratando CTRL+C, chamada kill interna.\n");
}
     
int main (void){
	signal(SIGINT, SIGINT_handler);

	kill(getpid(), SIGINT);
	kill(getpid(), SIGKILL);
}
