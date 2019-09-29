__kernel void matrixElementPower(__global int *A, int rowA)
{
    int row = get_global_id(1);
    int column = get_global_id(0);
    printf("(%d, %d) = %d\n", row, column, (row * rowA + column));
    int index = row * rowA + column + row;
    int i;
    int val = A[index];
    for(i = 0; i < row; i++)
        val *= A[index];
    A[index] = val;
    
}
