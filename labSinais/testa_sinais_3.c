#include <sys/types.h>
#include <signal.h>
#include <stdio.h>

void tratamento(int sigNumb) {
    if (sigNumb==SIGUSR1) 
    	printf("Gerado SIGUSR1\n");
    else 
    	if (sigNumb==SIGUSR2) 
    	   printf("Gerado SIGUSR2\n");
    	else 
    	   printf("Gerado %d\n",sigNumb); 
}

int main() {
    if (signal(SIGUSR1,tratamento)==SIG_ERR)
        printf("Erro na ligacao USER1\n");
    if (signal(SIGUSR2,tratamento)==SIG_ERR)
        printf("Erro na ligacao USER2\n");
    for(;;) 
        pause(); 
}
