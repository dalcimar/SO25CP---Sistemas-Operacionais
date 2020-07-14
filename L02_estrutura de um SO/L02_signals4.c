#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void SIGSEGV_handler(){
	printf("Tratando exceção segmentation violation.\n");
}
     
int main (void){
	signal(SIGSEGV, SIGSEGV_handler);

	int *pA=0x0;
	*pA=1;
}


