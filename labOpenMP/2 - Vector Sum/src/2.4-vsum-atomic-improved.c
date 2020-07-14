#include <omp.h>

long int sum(long int *v, long int n){
	long int i, sum = 0, sum_local;
	int myid, nthreads;

	#pragma omp parallel private(i, myid, sum_local) shared(sum, nthreads)
	{
		myid = omp_get_thread_num();
		#pragma omp single
		nthreads = omp_get_num_threads();

		sum_local = 0;
		for(i = myid; i < n; i += nthreads)
			sum_local += v[i];

		#pragma omp atomic
		sum += sum_local;
	}
	
	return sum;
}