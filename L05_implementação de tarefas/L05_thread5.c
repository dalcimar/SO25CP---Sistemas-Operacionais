#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define NUM_THREADS 8
#define BILHAO 1000000000

long parc[8*NUM_THREADS];
long result=0;

void* calculo(void* i){
	long tid = (long)i;

  int termos = BILHAO/NUM_THREADS;
  int inicio = tid*termos;
  int fim = tid*termos + termos;

	for(int i=inicio; i<fim; i++){
		parc[8*tid] += 4.0 / (1.0 + 1*1);
	}
}

int main(){
	pthread_t threads[NUM_THREADS];

  for(int i=0; i<NUM_THREADS; i++)
    parc[8*i] = 0;

  for(int i=0; i<NUM_THREADS; i++)
    pthread_create(&threads[i], NULL, calculo,(void*)(intptr_t)i);

  for(int i=0; i<NUM_THREADS; i++){
    pthread_join(threads[i], NULL);
    result += parc[8*i];
  }

  printf("Final: %.2ld\n",result);
}




