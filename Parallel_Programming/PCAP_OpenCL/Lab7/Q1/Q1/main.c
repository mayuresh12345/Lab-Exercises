//
//  main.c
//  Q1
//
//  Created by Tanmay Gulati on 09/03/19.
//  Copyright © 2019 Tanmay Gulati. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <OpenCL/opencl.h>

// Max source size of the kernel string
#define MAX_SIZE (0x100000)

// Width and height of matrices
#define WA 3
#define HA 2
#define BLOCK_SIZE 1

int main(void)
{
    int size_A = WA * HA;
    
    int *a = (int *)malloc(size_A * sizeof(int));
    
    FILE *fp;
    char *source_str;
    size_t source_size;
    
    fp = fopen("/Users/tanmaygulati/Work/3rd Year/PCAP\ OpenCL/Lab7/Q1/Q1/matrixElementPower.cl", "r");
    if(!fp)
    {
        printf("Failed to load kernel.\n");
        exit(1);
    }
    source_str = (char *)malloc(MAX_SIZE);
    source_size = fread(source_str, 1, MAX_SIZE, fp);
    
    fclose(fp); // close the file pointer
    int i;
    
    printf("Enter A: \n");
    for(i = 0; i < size_A; i++)
        scanf("%d", &a[i]);
    
    
    
    // Get platform and device information
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    
    cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_CPU, 1, &device_id, &ret_num_devices);
    
    // Create an OpenCL context
    cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
    
    // Create a command queue
    cl_command_queue command_queue = clCreateCommandQueue(context, device_id, NULL, &ret);
    
    // Create memory buffers on the device for each vector
    cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, size_A * sizeof(int), NULL, &ret);
    
    
    // Copy the lists A and B to their respective memory buffers
    ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0, size_A * sizeof(int), a, 0, NULL, NULL);
    
    // Create a program from the kernel source
    cl_program program = clCreateProgramWithSource(context, 1, (const char **)&source_str, (const size_t *)&source_size, &ret);
    
    // Build the program
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
    
    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "matrixElementPower", &ret);
    
    // Set the arguments of the kernel
    int heightA = WA;
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&a_mem_obj);
    ret = clSetKernelArg(kernel, 1, sizeof(int), &heightA);
    
    size_t localWorkSize[2] = {BLOCK_SIZE, BLOCK_SIZE};
    size_t globalWorkSize[2] = {WA, HA};
    
    ret = clEnqueueNDRangeKernel(command_queue, kernel, 2, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL);
    clFinish(command_queue);
    
    ret = clEnqueueReadBuffer(command_queue, a_mem_obj, CL_TRUE, 0, size_A * sizeof(int), a, 0, NULL, NULL);
    
    printf("Matrix A = \n");
    for(i = 0; i < size_A; i++)
    {
        printf("%d\t", a[i]);
        if(((i + 1) % WA) == 0)
            printf("\n");
    }
    
    free(source_str);
    clReleaseContext(context);
    clReleaseKernel(kernel);
    clReleaseCommandQueue(command_queue);
    getchar();
    
}
