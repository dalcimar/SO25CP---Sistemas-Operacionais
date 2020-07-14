#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <inttypes.h>

 
#define NUM_THREADS 16
 
int x=0;
 
void* threadBody (void *id){
   long tid = (long)id;
   x++;
   printf("t%ld: Ola! (x=%d)\n", tid, x);
   sleep(3);
   x++;
   printf("t%ld: Tchau! (x=%d)\n", tid, x);
   return (void*)99;
}
 
int main()
{
   pthread_t thread [NUM_THREADS];
   long i, status;
   pthread_attr_t attr;   
 
   pthread_attr_init(&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
 
    for (i=0; i<NUM_THREADS; i++){
        printf("Main: criando thread %ld\n", i);
        status = pthread_create (&thread[i], &attr, threadBody, (void*)i);
        if (status){
            perror("pthread_create");
            exit(1);
        }
    }
    
    for (i=0; i<NUM_THREADS; i++){
        void* result;
        printf("Main: aguardando thread %ld\n", i);
        long err = pthread_join(thread[i], &result);
        //printf("Thread %ld returned %ld ... is there any error? err=%ld\n", i,(uintptr_t)result,err);
    }
 
    pthread_attr_destroy(&attr);
    
    pthread_exit(NULL) ;
}
