#include <omp.h>

long int sum(long int *v, long int n){
	long int i, sum = 0, sum_local;

	#pragma omp parallel private(i, sum_local) shared(sum)
	{
		sum_local = 0;
		#pragma omp for
		for(i = 0; i < n; i++)
			sum_local += v[i];

		#pragma omp atomic
		sum += sum_local;
	}
	
	return sum;
}