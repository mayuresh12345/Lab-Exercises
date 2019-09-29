//
//  main.c
//  Q3
//
//  Created by Tanmay Gulati on 07/03/19.
//  Copyright © 2019 Tanmay Gulati. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include <OpenCL/opencl.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE (0x100000)

int main(void)
{
    time_t start, end;
    start = clock();
    
    char tempstr[100];
    int i;
    
    printf("Enter the string: \n");
    scanf("%s", tempstr);
    
    int len = strlen(tempstr);
    char *str = (char *)malloc(sizeof(char) * len);
    
    strcpy(str, tempstr);
    
    FILE *fp;
    char *source_str;
    size_t source_size;
    
    fp = fopen("/Users/tanmaygulati/Work/3rd Year/PCAP\ OpenCL/Lab6/Q3/Q3/reverse.cl", "r");
    
    if(!fp)
    {
        printf("Failed to load to kernel\n");
        exit(1);
    }
    source_str = (char *)malloc(MAX_SIZE);
    source_size = fread(source_str, 1, MAX_SIZE, fp);
    fclose(fp);
    
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    
    cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_CPU, 1, &device_id, &ret_num_devices);
    
    // Creating an OpenCL Context
    cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
    
    // Create a command queue
    cl_command_queue command_queue = clCreateCommandQueue(context, device_id, CL_QUEUE_PROFILING_ENABLE, &ret);
    
    // Create memory buffers on the device for input and output string
    cl_mem s_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, len * sizeof(char), NULL, &ret);
    cl_mem t_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, len * sizeof(char), NULL, &ret);
    
    // Copy the input string into respective memory buffer
    ret = clEnqueueWriteBuffer(command_queue, s_mem_obj, CL_TRUE, 0, len * sizeof(char), str, 0, NULL, NULL);
    
    // Create a program from the kernel source
    cl_program program = clCreateProgramWithSource(context, 1, (const char **)&source_str, (const size_t *)&source_size, &ret);
    
    // Build the program
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
    
    // Create the OpenCL Kernel
    cl_kernel kernel = clCreateKernel(program, "reverse", &ret);
    
    // Set the arguments of the kernel
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&s_mem_obj);
    ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&t_mem_obj);
    ret = clSetKernelArg(kernel, 2, sizeof(int), &len);
    
    // Set the global work size as string length
    size_t global_item_size = len;
    size_t local_item_size = 1;
    
    // Execute the OpenCL kernel for entire string in parallel
    cl_event event;
    ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, &event);
    time_t stime = clock();
    
    // Kernel execution must be finished before calculating time
    ret = clFinish(command_queue);
    
    cl_ulong time_start, time_end;
    double total_time;
    
    // Find the kernel execution start time
    clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(time_start), &time_start, NULL);
    
    // Find the kernel execution end time
    clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(time_end), &time_end, NULL);
    total_time = (double)(time_end - time_start);
    
    // Read the result in memory buffer on the device to the local variable strres
    char *strres = (char *)malloc(sizeof(char) * len);
    ret = clEnqueueReadBuffer(command_queue, t_mem_obj, CL_TRUE, 0, len * sizeof(char), strres, 0, NULL, NULL);
    printf("Done\n");
    strres[len] = '\0';
    printf("\nResultant toggled string is %s\n", strres);
    
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(s_mem_obj);
    ret = clReleaseMemObject(t_mem_obj);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);
    
    end = clock();
    
    printf("\nTime taken to execute the KERNEL in milliseconds = %0.3f msec\n\n", total_time/1000000);
    printf("\nTime taken to execute the whole program in seconds : %0.3f Seconds\n", (end - start) / (double) CLOCKS_PER_SEC);
    
    free(str);
    free(strres);
    return 0;
    
}
