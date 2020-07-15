#include <stdio.h> 
#include <unistd.h>
#include <pthread.h>

int x;

void* thr_func(void *arg){
	x++;
	printf("I am thread %ld and my x is %d\n", pthread_self(), x);
	pthread_exit(0);
}

int main(void){
	pthread_t tid;
	x=0;
	
	pthread_create(&tid, NULL, thr_func, NULL);
	sleep(1);
	printf("I am thread %ld and my x is %d\n", pthread_self(), x);
	
	pthread_exit(0);
}

