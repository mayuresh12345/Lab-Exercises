__kernel void mat_exp(__global int *A, int widthA){
	int row	 = get_global_id(1);
	int col = get_global_id(0);
	int exp = 1;
	
	for(int i = 0; i < row+1; i++)
		exp *= A[row*widthA+col];
	
	A[row*widthA+col] = exp;
}
