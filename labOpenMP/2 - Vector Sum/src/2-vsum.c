long int sum(long int *v, long int n){
	long int i, sum = 0;
	
	for(i = 0; i < n; i++)
		sum += v[i];
	
	return sum;
}