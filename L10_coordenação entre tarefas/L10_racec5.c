#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

#define NUM_THREADS 2

long saldo=0;

int lock; // variável de trava

void enter(){
		int key = 1 ;
		while(key){
			asm("xchg %0, %1" : "+q" (key), "+m" (lock));
		}	
		//while (__sync_val_compare_and_swap(&lock, 0, 1) != 0){
    //}
}

void leave(){
	lock = 0; // libera a seção crítica
}

void* depositar(void* v){
	int tid = (int)(long)v;
	
	for(int i=0;i<10000;i++){
		enter(tid);
		saldo += 1;
		leave(tid);
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



