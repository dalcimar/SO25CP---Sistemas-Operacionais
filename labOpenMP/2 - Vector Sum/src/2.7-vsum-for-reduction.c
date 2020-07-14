#include <omp.h>

long int sum(long int *v, long int n){
	long int i, sum = 0;

	#pragma omp parallel for default(shared) private(i) reduction(+ : sum)
	for(i = 0; i < n; i++)
		sum += v[i];	
	
	return sum;
}