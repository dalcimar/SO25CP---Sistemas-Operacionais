#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void SIGFPE_handler(){
	printf("Tratando exceção division by zero.\n");
}
 
int main (void){
	signal(SIGFPE, SIGFPE_handler);

	int a=1;
	int b=0;
	b = a/b;
}

