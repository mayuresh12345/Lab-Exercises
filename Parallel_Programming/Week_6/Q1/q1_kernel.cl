__kernel void ascii_rev(__global char *A, __global char *B){
	int i = get_global_id(0);
	int d;
	int n = (int)A[i];
	int rev = 0;
	while(n > 0)
	{
		d = n % 10;
		rev = rev * 10 + d;
		n /= 10;
	}
	B[i] = (char)rev;
	
}
