// 1 - Analise seu código e o comente detalhadamente.
// 2 - A ordem de criação, ativação e encerramento das threads é a mesma? Por que?
// 3 - Desenhe o diagrama de tempo de sua execução.

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
#define NUM_THREADS 16
 
void *threadBody (void *id)
{
   //long tid = (long) id ;
   long tid = *((long*)(&id));
 
   printf ("t%02ld: Ola!\n", tid) ;
   sleep (3) ;   
   printf ("t%02ld: Tchau!\n", tid) ;
 
   pthread_exit (NULL) ;
}
 
int main (int argc, char *argv[])
{
   pthread_t thread [NUM_THREADS] ;
   long i, status ;
 
   for (i=0; i<NUM_THREADS; i++)
   {
      printf ("Main: criando thread %02ld\n", i) ;
 
      status = pthread_create (&thread[i], NULL, threadBody, (void *) i) ;
 
      if (status)
      {
         perror ("pthread_create") ;
         exit (1) ;
      }
   }
   pthread_exit (NULL) ;
}
