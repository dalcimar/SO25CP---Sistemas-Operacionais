#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 2

int c = 0;

int turn=0;

void *fnC(void *id)
{
   long tid = *((long*)(&id));
   
   for(int i=0;i<10;i++){ 
   printf("Thread t%02ld: reads c, value is %d \n", tid, c);
      while (turn!=tid); //entra na região critica ou espera
      int x=c;
      printf("Thread t%02ld: reads c, value is %d \n", tid, c);
   
      //if (x==c){
         c++;
         printf("Thread t%02ld: add 1 to c, value is now %d \n", tid, c);
      //}
      turn = 1-tid; //passa a vez
      //
	  //if(tid==1)
      	//sleep(30);
   }
}

int main()
{
   int rt1, rt2;
   pthread_t thread[NUM_THREADS] ;
   
   /* Create threads */
   for (int i=0; i<NUM_THREADS; i++)
      pthread_create(&thread[0], NULL, &fnC, (void*)i);
   
   /* Wait for all threads to finish */
   for (int i=0; i<NUM_THREADS; i++)
      pthread_join (thread[i], NULL) ;
   
   printf ("Final value of c %d \n", c);
   return 0;

}
