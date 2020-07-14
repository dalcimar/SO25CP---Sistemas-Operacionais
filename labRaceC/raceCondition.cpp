#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 2

int c = 0;
int lock = 0;
void *fnC(void *id)
{
   long tid = *((long*)(&id));
   
   for(int i=0;i<10;i++){
      int x=c;
      printf("Thread t%02ld: reads c, value is %d \n", tid, c);
      if (lock == 0){
          lock = 1;
      //if (x==c){
         c++;
         printf("Thread t%02ld: add 1 to c, value is now %d \n", tid, c);
         lock = 0;
      //
      }
   }
}


int main()
{
    pthread_t thread[NUM_THREADS] ;
    /* Create threads */
    for(int i=0;i<NUM_THREADS;i++)
      pthread_create(&thread[i], NULL, &fnC, (void*)i);

    /* Wait for all threads to finish */
    for (int i=0; i<NUM_THREADS; i++)
      pthread_join (thread[i], NULL) ;

    printf ("Final value of c %d \n", c);
    return 0;

}
