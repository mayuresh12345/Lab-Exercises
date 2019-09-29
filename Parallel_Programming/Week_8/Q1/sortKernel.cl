__kernel void parallelSort(__global char *A, __global char *RES){
	int id = get_global_id(0), data = A[id];
	int n = get_global_size(0);
	int pos = 0;
	
	for(int i = 0; i < n; i++){
		if((A[i] < data) || (A[i] == data && i < id))
			pos++;
	}

		
	RES[pos] = data;
	
}