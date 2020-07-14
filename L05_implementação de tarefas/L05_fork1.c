#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void) {
	int x = 0;

	fork();
	x = 1;
	printf("I am process %ld and my x is %d\n", (long)getpid(), x);
	
	exit(0);
}
