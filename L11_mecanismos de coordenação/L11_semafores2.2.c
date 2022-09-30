#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <semaphore.h>

#define ever ;;

sem_t b, l, m;

void* bart(void* v){
	for(ever){
		sem_wait(&b);
		printf("bart-->");
		sem_post(&l);
	}
}

void* lisa(void* v){
	for(ever){
		sem_wait(&l);
		printf("lisa-->");
		sem_post(&m);
	}
}

void* maggie(void* v){
	for(ever){
		sem_wait(&m);
		printf("maggie-->");
		sem_post(&b);
	}
}

int main(){
	pthread_t thread[3];
	sem_init(&b, 0, 1); // Bart inicia livre para executar
	sem_init(&l, 0, 0); // Lisa inicia bloqueada
	sem_init(&m, 0, 0); // Maggie inicia bloqueada

	pthread_create(&thread[0], NULL, &bart, NULL);
	pthread_create(&thread[1], NULL, &lisa, NULL);
	pthread_create(&thread[2], NULL, &maggie, NULL);

	for(int i=0; i<3; i++)
		pthread_join (thread[i], NULL);

	exit(0);
}



