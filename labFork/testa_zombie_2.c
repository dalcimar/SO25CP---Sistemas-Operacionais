#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

/* rodar o programa em foreground */

int main() 
{
    int pid ;
    printf("Eu sou o processo pai, PID =  %d, e eu vou criar um filho.\n",getpid()) ;
    printf("Bem, eu j√° coloquei mais um filho no mundo e agora vou terminar. Fui!\n") ;
    pid = fork() ;
    if(pid == -1) {/* erro */
        perror("E impossivel criar um filho") ;
        exit(-1) ;
    }
    else if(pid == 0) {/* filho */
        printf("Eu sou o filho, PID = %d. Estou vivo mas vou dormir um pouco. Use o comando ps -l para conferir o meu estado (S=sleep) e o PID do meu pai. Notou algo diferente no PID do meu pai? Notou que eu n„o virei um zumbi? Daqui a pouco eu acordo.\n",getpid()) ;
        sleep(60);
        printf("Acordei! Vou terminar agora. Use ps -l novamente.\n") ;
        exit(0);
    }
    else {/* pai */
        /*	 for(;;) ;  pai bloqueado em loop infinito */
    }
}

