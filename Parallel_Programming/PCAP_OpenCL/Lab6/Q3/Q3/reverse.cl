__kernel void reverse(__global char *A, __global char *B, int len)
{
    int id = get_global_id(0);
    char temp = A[id];
    B[len - id - 1] = temp;
}
