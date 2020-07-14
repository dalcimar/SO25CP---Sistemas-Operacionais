//1 - Analise seu código e o comente detalhadamente.
//2 - Compare a evolução da variável x neste programa com aquela que ocorreria em um programa equivalente usando a chamada de sistema fork.
//3 - Desenhe o diagrama de tempo de sua execução, mostrando a evolução do valor da variável x.

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
#define NUM_THREADS 16
 
int x = 0 ;
 
void *threadBody (void *id)
{
   //long tid = (long) id ;
   long tid = *((long*)(&id));
   x++ ;
   printf ("t%02ld: Ola!   (x=%02d)\n", tid, x) ;
   sleep (3) ;
   x++ ;
   printf ("t%02ld: Tchau! (x=%02d)\n", tid, x) ;
 
   pthread_exit (NULL) ;
}
 
int main (int argc, char *argv[])
{
   pthread_t thread [NUM_THREADS] ;
   long i, status ;
 
   for (i=0; i<NUM_THREADS; i++)
   {
      printf ("Main: criando thread %02ld\n", i);
 
      status = pthread_create (&thread[i], NULL, threadBody, (void *) i) ;
 
      if (status)
      {
         perror ("pthread_create") ;
         exit (1) ;
      }
   }
   pthread_exit (NULL) ;
}


