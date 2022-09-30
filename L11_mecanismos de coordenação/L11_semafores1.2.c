#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <semaphore.h>

#define NUM_THREADS 4
#define ever ;;

double saldo=0;
sem_t lock;

void* depositar(void* v){
	int tid = (int)(long)v;
	
	for(int i=0;i<10000;i++){
		sem_wait(&lock);
		saldo += 1;
		//sem_post(&lock);
	}
}

void* sacar(void* v){
	int tid = (int)(long)v;
	
	for(int i=0;i<10000;i++){
		sem_wait(&lock);
		//printf("asdfafd %d\n",tid);
		saldo -= 0.5;
		sem_post(&lock);
	}
}

int main(){
	pthread_t threadd[NUM_THREADS];
	pthread_t threads[NUM_THREADS];
	sem_init(&lock, 0, 1);

	for(int i=0;i<NUM_THREADS;i++)
		pthread_create(&threadd[i], NULL, &depositar, (void*)(intptr_t)i);
		
	for(int i=0;i<NUM_THREADS;i++)
		pthread_create(&threads[i], NULL, &sacar, (void*)(intptr_t)i);
	
	for(int i=0;i<NUM_THREADS; i++)
		pthread_join(threadd[i], NULL);
		
	for(int i=0;i<NUM_THREADS; i++)
		pthread_join(threads[i], NULL);

	printf("Final value of c %.2f \n", saldo);

	exit(0);
}



