__kernel void strToggle(__global char *A, __global char *B)
{
    int i = get_global_id(0);
    if(A[i] >= 'A' && A[i] <= 'Z')
        A[i] += 32;
    else
        A[i] -= 32;
    B[i] = A[i];
}
