__kernel void mat_mul(__global int *A, __global int *B, __global int *C, int widthA, int widthB){
	int row	 = get_global_id(1);
	int col = get_global_id(0);
	int sum = 0;
		
	for(int i = 0; i < widthA; i++){
		sum += A[row*widthA+i]*B[i*widthB+col];
	}
	C[row*widthB+col] = sum;
}
