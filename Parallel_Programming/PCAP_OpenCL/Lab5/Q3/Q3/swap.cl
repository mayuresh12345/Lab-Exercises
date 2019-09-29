__kernel void swap(__global int *A, int len)
{
    int i = get_global_id(0);
//    printf("%d\t", i);
    
//    printf("%d", len);
    
    if(i <= len/2)
    {
        int temp = A[i];
        A[i] = A[i+2];
        A[i+2] = temp;
    }
}
