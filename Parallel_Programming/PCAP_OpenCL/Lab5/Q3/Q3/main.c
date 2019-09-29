//
//  main.c
//  Q3
//
//  Created by Tanmay Gulati on 24/02/19.
//  Copyright © 2019 Tanmay Gulati. All rights reserved.
//

#include <stdio.h>
#include <OpenCL/opencl.h>
#include <stdlib.h>

// Max source size of kernel string
#define MAX_SIZE (0x100000)

int main(void)
{
    // Create two input vectors
    int i;
    int LIST_SIZE;
    
    printf("How many elements : ");
    scanf("%d", &LIST_SIZE);
    
    int *A = (int *)malloc(sizeof(int) * LIST_SIZE);
    printf("Enter the values : \n");
    // Initialize the input vectors
    for(i = 0; i < LIST_SIZE; i++)
        scanf("%d", &A[i]);
    
    int *B = (int *)malloc(sizeof(int) * LIST_SIZE);
    
    for(i = 0; i < LIST_SIZE; i++)
        B[i] = 0;
    
    FILE *fp;
    char *source_str;
    size_t source_size;
    
    // Load the kernel source code into array source_str
    fp = fopen("/Users/tanmaygulati/Work/3rd Year/PCAP\ OpenCL/Lab5/Q3/Q3/swap.cl", "r");
    
    if(!fp)
    {
        printf("Failed to load kernel\n");
        exit(0);
    }
    
    source_str = (char *)malloc(sizeof(char) * MAX_SIZE);
    source_size = fread(source_str, 1, MAX_SIZE, fp);
    
    fclose(fp);
    
    // Get platform and device information
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    
    cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_CPU, 1, &device_id, &ret_num_devices);
    
    // Create an OpenCL Context
    cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
    
    // Create a command queue
    cl_command_queue command_queue = clCreateCommandQueue(context, device_id, NULL, &ret);
    
    // Create memory buffers for the devices A, B, C
    cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, LIST_SIZE * sizeof(int), NULL, &ret);
    cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, LIST_SIZE * sizeof(int), NULL, &ret);
    
    
    // Copy the lists A and B into their respective memory buffers
    ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0, LIST_SIZE * sizeof(int), A, 0, NULL, NULL);
    ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0, LIST_SIZE * sizeof(int), B, 0, NULL, NULL);
    
    // Create a program with kernel source
    cl_program program = clCreateProgramWithSource(context, 1, (const char *)&source_str, (const size_t *)&source_size, &ret);
    
    // Build the program
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
    
    // Create the OpenCL kernel object
    cl_kernel kernel = clCreateKernel(program, "swap", &ret);
    
    // Set the kernel arguments
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&a_mem_obj);
    ret = clSetKernelArg(kernel, 1, sizeof(int), &LIST_SIZE);
    
    
    
    // Execute the OpenCL kernel on the array
    size_t global_item_size = LIST_SIZE;
    size_t local_item_size = 1;
    
    cl_event event;
    ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);
    
    ret = clFinish(command_queue);
    
    ret = clEnqueueReadBuffer(command_queue, a_mem_obj, CL_TRUE, 0, LIST_SIZE * sizeof(int), A, 0, NULL, NULL);
    
    for(int i = 0; i < LIST_SIZE; i++)
        printf("%d ", A[i]);
    printf("\n\n");
    
    // Clean up
    ret = clFlush(command_queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(a_mem_obj);
    ret = clReleaseMemObject(b_mem_obj);
    
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);
    
    free(A);
    free(B);
    
    getchar();
    return 0;
    
    
}
