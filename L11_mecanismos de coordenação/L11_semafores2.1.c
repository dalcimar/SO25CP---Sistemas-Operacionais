#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <semaphore.h>

#define ever ;;

sem_t b, l, m;

void* bart(void* v){
	for(ever){
		printf("bart-->");
	}
}

void* lisa(void* v){
	for(ever){
		printf("lisa-->");
	}
}

void* maggie(void* v){
	for(ever){
		printf("maggie-->");
	}
}

int main(){
	pthread_t thread[3];

	pthread_create(&thread[0], NULL, &bart, NULL);
	pthread_create(&thread[1], NULL, &lisa, NULL);
	pthread_create(&thread[2], NULL, &maggie, NULL);

	for(int i=0; i<3; i++)
		pthread_join (thread[i], NULL);

	exit(0);
}



