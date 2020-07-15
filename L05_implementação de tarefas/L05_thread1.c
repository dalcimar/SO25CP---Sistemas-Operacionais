// Exemplo de uso de threads Posix em C no Linux
// Compilar com gcc exemplo.c -o exemplo -lpthread
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 5

void* print_hello (void *tid){ // cada thread vai executar esta função
	printf ("%ld: Hello World!\n", (long)tid);
	pthread_exit(0); // encerra a thread "secundária" 
}

int main(int argc, char *argv[]){
	pthread_t thread[NUM_THREADS];
	long status, i;

	for(i=0; i<NUM_THREADS; i++){
		printf("Creating thread %ld\n", i);
		status = pthread_create(&thread[i], NULL, print_hello, (void*)i); // cria as demais threads

		if (status){ // ocorreu um erro
			perror("pthread_create");
			exit(-1);
		}
	}
	
	pthread_exit(0); // encerra a thread "main" 
}
