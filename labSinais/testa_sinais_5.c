#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>

int main(void ) {
  void (*oldHandler) (int); 	   /* Para guardar o tratador original */
  

  printf("I can be Control-C’ed\n");
  sleep(3);
  oldHandler = signal (SIGINT, SIG_IGN);  /* Ignorar Control-C */
  printf("I’m protected from Control-C now\n");
  sleep(3);
  signal (SIGINT, oldHandler);         /* Restaurar o tratador original */
  printf("I can be Control-C’ed again\n");
  sleep(3);
  printf("Bye!\n"); 
}
