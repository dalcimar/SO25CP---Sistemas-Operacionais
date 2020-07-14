// 1 - Analise seu código e o comente detalhadamente.
// 2 - Explique o objetivo do parâmetro attr e da chamada pthread_join.
// 3 - Desenhe o diagrama de tempo de sua execução.
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
#define NUM_THREADS 16
 
void* threadBody(void *id)
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
   pthread_attr_t attr ;   
   long i, status ;
 
   pthread_attr_init (&attr) ;
   pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_JOINABLE) ;
 
   for(i=0; i<NUM_THREADS; i++)
   {
      printf ("Main: criando thread %02ld\n", i) ;
 
      status = pthread_create (&thread[i], &attr, threadBody, (void *) i) ;
      if (status)
      {
         perror ("pthread_create") ;
         exit (1) ;
      }
   }
 
   for (i=0; i<NUM_THREADS; i++)
   {
      printf ("Main: aguardando thread %02ld\n", i);
      status = pthread_join (thread[i], NULL) ;
      if (status)
      {
         perror ("pthread_join") ;
         exit (1) ;
      }
   }
 
   pthread_attr_destroy (&attr) ;
 
   pthread_exit (NULL) ;
}
