#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "src/sum.h"

int main(int argc, char **argv){
	char *awnser[] = { "bad", "ok" };
	
	long int i, sumv, n;
	double start, end, elapsed;
	
	if(argc < 2){
		fprintf(stderr, "Usage: %s <number of elements>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	n = atol(argv[1]);
	n *= 10e6;
	
	printf("number of elements: %ld x 10E6\n", (long int) (n / 10e6));
	
	long int *vector = (long int *) calloc(n, sizeof(long int));
	if(vector == NULL){
		fprintf(stderr, "Out of memory!\n");
		exit(EXIT_FAILURE);
	}
		
	for(i = 0; i < n; i++)
		vector[i] = 1;
	
	start = omp_get_wtime();
	sumv = sum(vector, n);
	end = omp_get_wtime();
	
	elapsed = end - start;
	
	printf("sum value is %s\ntime: %.3f seconds\n", awnser[sumv == n], elapsed);

	free(vector);
	
	return 0;
}