__kernel void ascii_rev(__global char *A, __global char *B)
{
    int id = get_global_id(0);
    printf("%d ", id);
    int num = (int)A[id];
    int d = 0, sum = 0;
    while(num > 0)
    {
        d = num % 10;
        sum = sum * 10 + d;
        num /= 10;
    }
    B[id] = (char)sum;
}
