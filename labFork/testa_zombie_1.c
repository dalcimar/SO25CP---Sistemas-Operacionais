#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

/* rodar o programa em background */

int main() 
{
    int pid ;
    printf("Eu sou o processo pai, PID =  %d, e eu vou criar um filho.\n",getpid()) ;
    printf("Agora estou entrando em um loop infinito. Tchau!\n") ;
    pid = fork() ;
    if(pid == -1) {/* erro */
        perror("E impossivel criar um filho") ;
        exit(-1) ;
    }
    else if(pid == 0) {/* filho */
        printf("Eu sou o filho, PID = %d. Estou vivo mas vou dormir um pouco. Enquanto isso, use o comando ps -l para conferir o meu PID, o meu estado (S=sleep), o PID do meu pai e o estado do meu pai (R=running). Daqui a pouco eu acordo.\n",getpid()) ;
        sleep(20) ;
        printf("Acordei! Vou terminar agora. Confira novamente essas informacoes. Nãooooooo!!! Virei um zumbi!!!\n") ;
        exit(0) ;
    }
    else { /* pai */
        for(;;) ; /* pai bloqueado em loop infinito */
    }
}

