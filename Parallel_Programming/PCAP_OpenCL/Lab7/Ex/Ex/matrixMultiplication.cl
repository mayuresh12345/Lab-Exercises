__kernel void matrixMultiplication(__global int *A, __global int *B, __global int *C, int wA, int wB)
{
    int row = get_global_id(1);
    int col = get_global_id(0);
    int sum = 0;
    
    for(int i = 0; i < wA; i++)
        sum += A[row * wA + i] * B[i * wB + col];
    C[row * wB + col] = sum;
}
