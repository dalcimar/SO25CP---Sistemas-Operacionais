#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 50

void enter_region() {
    asm(
        ".data\n\t"
        "lock:\n\t"
        ".byte 0\n\t"
        ".text\n\t"
        "movb $1, %al\n\t" /* move 1 to AL */

        "_enter_region:\n\t"
        "xchgb (lock),%al\n\t" 
        "cmp $0, %al\n\t"
        "jne _enter_region\n\t"

    );
}

void leave_region() {
    asm("movb $0, (lock)");
}

int c = 0;
void *fnC(void *id)
{
   //long tid = (long) id ;
   long tid = *((long*)(&id));
   
   enter_region();
   int x=c;
   printf("Thread t%02ld: reads c, value is %d \n", tid, c);

   if (x==c){
      c++;
      printf("Thread t%02ld: add 1 to c, value is now %d \n", tid, c);
   }
   leave_region();  
}


int main()
{
    int rt1, rt2;
    pthread_t thread[NUM_THREADS] ;
    // Create two threads
    for(int i=0;i<NUM_THREADS;i++)
      pthread_create(&thread[i], NULL, &fnC, (void*)i);

    // Wait for all threads to finish
    for (int i=0; i<NUM_THREADS; i++)
      pthread_join (thread[i], NULL) ;

    printf ("Final value of c %d \n", c);
    return 0;

}
