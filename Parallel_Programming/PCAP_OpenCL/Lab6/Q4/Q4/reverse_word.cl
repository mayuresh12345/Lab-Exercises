__kernel void reverse_word(__global char *A, __global char *B, int len, __global int *indices)
{
    int id = get_global_id(0);
//    printf("id = %d, index = %d\n", id, indices[id]);
    int i = 0;
    int startingIndex = indices[id] + 1;
    int endingIndex = indices[id + 1];
    
    int t = 1;
    for(i = startingIndex; i < endingIndex; i++)
    {
        B[i] = A[endingIndex - (t++)];
        printf("%c", B[i]);
    }
    B[i] = ' ';
    
}
