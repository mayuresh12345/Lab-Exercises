__kernel void multipleStrings(__global char *A, __global char *B, int len, int N)
{
    int id = get_global_id(0);
//    printf("%d ", id);
//    for(int i = 0; i < N; i++)
//        B[i*N + id] = A[id];
    for(int i = 0; i < len; i++)
        B[id * N + i] = A[i];
}
