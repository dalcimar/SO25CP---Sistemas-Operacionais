#include <stdio.h>
#include <unistd.h>

int main()
{
    printf ("Eu sou o processo PID=%d e estou executando o programa testa_exec_0\n", getpid()) ;
    printf ("Vou fazer um exec() agora!\n") ;
    execl("/bin/ls","ls","-la",NULL) ;
    printf ("Estou de volta! Vou continuar a execucao do programa testa_exec_0\n") ;
    return 1;
}
