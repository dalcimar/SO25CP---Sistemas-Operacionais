#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 

#define BILHAO 1000000000

long result=0;

void serialDotProduct(){
	long x;
	
	int inicio=0;
	int fim=BILHAO;
	
	for(int i=inicio; i<fim; i++){
		result += 4.0 / (1.0 + 1*1);
	}
}
 
int main(){
	serialDotProduct();
	printf("Final: %.2ld\n",result);
}
