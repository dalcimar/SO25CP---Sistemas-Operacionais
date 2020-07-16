#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

#define NUM_THREADS 4

long saldo=0;
int busy=0; // a seção está inicialmente livre


void enter(){ 
	while(busy){}; // espera enquanto a seção estiver ocupada
	busy = 1; // marca a seção como ocupada
}


void leave(){ 

	busy = 0; // libera a seção (marca como livre)
}

void* depositar(void* v){
	for(int i=0;i<100;i++){
		enter();
		saldo += 1;
		leave();
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



