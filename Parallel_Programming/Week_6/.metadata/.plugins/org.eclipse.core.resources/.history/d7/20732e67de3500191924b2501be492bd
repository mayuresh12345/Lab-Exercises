__kernel void repeat(__global char *A, __global char *B, __global int N){
	int i = get_global_id(0);
	
	if(N > 0)
	{
		for(int k = 0; k < N; k++)
		{
			B[i + k * strlen(A)] = A[i];
		}	
	} 
	N--;
	
}
