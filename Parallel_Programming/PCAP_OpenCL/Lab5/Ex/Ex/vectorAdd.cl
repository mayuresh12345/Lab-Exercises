__kernel void vectorAdd(__global int *A, __global int *B, __global int *C)
{
    int i = get_global_id(0);
    C[i] = A[i] + B[i];
}
