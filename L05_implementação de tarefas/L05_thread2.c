#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#define ever ;;

void* print_xs(void* p){
	for(ever){
		printf("i");
	}
}
    
int main(void){
	pthread_t tid;
	
	pthread_create(&tid, NULL, &print_xs, NULL);

	for(ever){
		printf("o");
	}

	pthread_exit(0);
}
