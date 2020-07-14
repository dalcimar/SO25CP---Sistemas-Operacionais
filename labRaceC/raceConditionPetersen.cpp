#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 2

int c = 0;

int turn;
int interested[2];

void enter_region(int process)
{
   int other;
   
   other = 1 - process;
   interested[process] = true;
   turn = process;
   while (turn == process && interested[other] == true) ;
}

void leave_region(int process)
{
   interested[process] = false;
}

void *fnC(void *id)
{
   //long tid = (long) id ;
   long tid = *((long*)(&id));
   
   for(int i=0;i<10;i++){
      enter_region(tid);
      int x=c;
      printf("Thread t%02ld: reads c, value is %d \n", tid, c);
   
      if (x==c){
         c++;
         printf("Thread t%02ld: add 1 to c, value is now %d \n", tid, c);
      }
      leave_region(tid); 
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
