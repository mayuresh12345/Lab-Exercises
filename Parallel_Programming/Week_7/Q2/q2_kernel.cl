__kernel void mat_ones_comp(__global int *A,__global int *B, int widthA){
	int row	 = get_global_id(1);
	int col = get_global_id(0);
	int max_col = get_global_size(0)-1;
	int max_row = get_global_size(1)-1;
	
	int val = A[row*widthA+col];
	int a,b;
	if(col != 0 && col != max_col && row != 0 && row != max_row){
		a = ( val & ~0 );
		b = ( ~val & 0 );
		val = (~a & ~b);
	}
	B[row*widthA+col] = val;
}
