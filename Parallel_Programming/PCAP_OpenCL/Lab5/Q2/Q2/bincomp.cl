__kernel void bincomp(__global int *A, __global int *B)
{
    int i = get_global_id(0);
    int d;
    int num = A[i];
    int sum = 0;
    while(num > 0)
    {
        d = num % 10;
        if(d == 1)
            d = 0;
        else
            d = 1;
        sum = sum * 10 + d;
        num /= 10;
    }
    B[i] = sum;
}
