#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <semaphore.h>

#define NUM_THREADS 4
#define ever ;;

long saldo=0;
sem_t lock, master;

void* depositar(void* v){
	int tid = (int)(long)v;
	
	for(int i=0;i<10000;i++){
		sem_wait(&lock);
		saldo += 1;
		sem_post(&lock);
	}
	sem_post(&master);
}

int main(){
	pthread_t thread[NUM_THREADS];
	sem_init(&lock, 0, 1);
	sem_init(&master, 0, 0);

	for(int i=0;i<NUM_THREADS;i++)
		pthread_create(&thread[i], NULL, &depositar, (void*)(intptr_t)i);
	
	for(int i=0;i<NUM_THREADS;i++)
		sem_wait(&master);
	
	printf("Final value of c %ld \n", saldo);

	exit(0);
}

