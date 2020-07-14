#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
    int pid ;
    printf("\nBom dia, eu me apresento. Sou o processo %d.\n",getpid());
    printf("Estou sentindo uma coisa crescendo dentro de minha barriga...");
    printf("Sera um filho?!?!\n");
    if (fork() == 0) {
       	printf("\tOi, eu sou %d, o filho de %d.\n",getpid(),getppid());
       	sleep(3);
       	printf("\tEu sou tao jovem, e ja me sinto tao fraco!\n");
       	printf("\tAh nao... Chegou minha hora!\n");
       	exit(7);
   }
   else {
        int ret1, status1 ;
        printf("Vamos esperar que este mal-estar desapareca.\n");
        ret1 = wait(&status1);
        if ((status1&255) == 0) {
          	printf("Valor de retorno do wait(): %d\n",ret1);
          	printf("Parametro de exit(): %d\n",(status1>>8));
          	printf("Meu filho morreu por causa de um simples exit.\n");
        }
        else
         	printf("Meu filho nao foi morto por um exit.\n");
          	
        printf("\nSou eu ainda, o processo %d.", getpid());
        printf("\nOh nao, recomecou! Minha barriga esta crescendo de novo!\n");
        if ((pid=fork()) == 0) {
          	printf("\tAlo, eu sou o processo %d, o segundo filho de %d\n",getpid(),getppid());
          	sleep(3) ;
          	printf("\tEu nao quero seguir o exemplo de meu irmao!\n") ;
          	printf("\tNao vou morrer jovem e vou ficar num loop infinito!\n") ;
          	for(;;);
        }
        else {
            int ret2, status2, s;
            printf("Este aqui tambem vai ter que morrer.\n");
            ret2 = wait(&status2) ;
            if ((status2&255) == 0) {
                printf("O filho nao foi morto por um sinal\n");
            }
            else {
                printf("Valor de retorno do wait(): %d\n",ret2);
                s = status2&255;
                printf("O sinal assassino que matou meu filho foi: %d\n",s);
            }
        }
    }
    exit(0);
}

