#include <omp.h>

long int sum(long int *v, long int n){
	long int i, sum = 0;
	int myid, nthreads;

	#pragma omp parallel private(i, myid) shared(sum, nthreads)
	{
		myid = omp_get_thread_num();
		#pragma omp single
		nthreads = omp_get_num_threads();

		for(i = myid; i < n; i += nthreads)
			#pragma omp atomic
			sum += v[i];
	}
	
	return sum;
}