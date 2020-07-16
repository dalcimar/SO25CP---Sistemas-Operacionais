#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

#define NUM_THREADS 4

long saldo=0;

void* depositar(void* v){
	for(int i=0;i<10000;i++){
		saldo = saldo+1;
	}
}


int main(){
    pthread_t thread[NUM_THREADS] ;

    for(int i=0;i<NUM_THREADS;i++)
      pthread_create(&thread[i], NULL, &depositar, (void*)(intptr_t)i);

    for(int i=0; i<NUM_THREADS; i++)
      pthread_join (thread[i], NULL);

    printf("Final value of c %ld \n", saldo);
    
    exit(0);
}



