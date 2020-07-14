#include <omp.h>

long int sum(long int *v, long int n){
	long int i, sum = 0, sum_local, init, end, slice;
	int myid, nthreads;

	#pragma omp parallel private(i, myid, sum_local, init, end) shared(sum, nthreads, slice)
	{
		myid = omp_get_thread_num();
		#pragma omp single
		{
		nthreads = omp_get_num_threads();
		slice = n / nthreads;
		}

		init = myid * slice;
		if(myid == nthreads - 1)
			end = n;
		else
			end = init + slice;

		sum_local = 0;
		for(i = init; i < end; i++)
			sum_local += v[i];

		#pragma omp atomic
		sum += sum_local;
	}
	
	return sum;
}