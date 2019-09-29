__kernel void dec2oct(__global int *A, __global int *B)
{
    int i = get_global_id(0);
    
    int num = A[i];
    
    int octalnum = 0, k = 1;
    
    while(num != 0)
    {
        octalnum += (num % 8) * k;
        num /= 8;
        k *= 10;
    }
    B[i] = octalnum;
}
