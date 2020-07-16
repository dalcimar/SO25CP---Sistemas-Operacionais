#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

#define NUM_THREADS 4

long saldo=0;

int turn=0; // inicia pela tarefa 0

void enter(int task){ // task vale 0, 1, ..., num_tasks-1
	while(turn != task){
	}
}

void leave(int task){
	turn = (turn+1)%NUM_THREADS; // passa para a próxima tarefa
}

void* depositar(void* v){
	long tid = (int)(long)v;
	
	for(int i=0;i<10000;i++){
		if(tid!=3){ // todas as tarefas querem usar a região critica?
			enter(tid);
			saldo += 1;
			leave(tid);
		}
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



