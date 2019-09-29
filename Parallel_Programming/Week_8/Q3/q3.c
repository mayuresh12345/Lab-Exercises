#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include <string.h>
#define MAX_SOURCE_SIZE (0x100000)

int main(void)
{
	int spaces[100], n[100];

	char str[1024], key[256];

	printf("Enter sentence : ");
	gets(str);

	int len = strlen(str);

	spaces[0] = -1;					//initilize to before start of string
	int j = 1;
	int words = 1;

	for (int i = 0; i < len; ++i)
	{
		if(str[i] == ' '){
			spaces[j++] = i;
			words++;
		}
	}

	spaces[j] = len;

	printf("\nNo. of Words = %d \n", words);

	printf("Space Indexes : ");

	for (int i = 0; i <= j; ++i)
	{
		printf("%d ", spaces[i]);
	}

	printf("\nEnter word to be searched : ");
	gets(key);

	int len2 = strlen(key);				// as string includes \n

	FILE* fp;
	char* source_str;
	size_t source_size;
	fp = fopen("q3_kernel.cl", "r");

	source_str = (char*) malloc(MAX_SOURCE_SIZE);
	source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
	fclose(fp);

	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_uint ret_num_devices, ret_num_platforms;

	cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);

	cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
	cl_command_queue command_queue = clCreateCommandQueue(context, device_id, NULL, &ret);

	cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, len*sizeof(char), NULL, &ret);			//sentence
	cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, (j+1)*sizeof(int), NULL, &ret);		//space array
	cl_mem c_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, len2*sizeof(char), NULL, &ret);		//key string
	cl_mem d_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(int), NULL, &ret);				//key_len
	cl_mem e_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, words*sizeof(int), NULL, &ret);				//number of occurences

	ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0, len*sizeof(char), str, 0, NULL, NULL);
	ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0, (j+1)*sizeof(int), spaces, 0, NULL, NULL);
	ret = clEnqueueWriteBuffer(command_queue, c_mem_obj, CL_TRUE, 0, len2*sizeof(char), key, 0, NULL, NULL);
	ret = clEnqueueWriteBuffer(command_queue, d_mem_obj, CL_TRUE, 0, sizeof(int), &len2, 0, NULL, NULL);
	cl_program program = clCreateProgramWithSource(context, 1, (const char**)&source_str, (const size_t*)&source_size, &ret);
	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

	if(ret != CL_SUCCESS){
        size_t len;
        char buffer[2048];
        printf("Error: Failed to build program executable!\n");
        clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
        printf("%s\n", buffer);
        exit(1);
    }



	cl_kernel kernel = clCreateKernel(program, "search", &ret);
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&a_mem_obj);
	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&b_mem_obj);
	ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&c_mem_obj);
	ret = clSetKernelArg(kernel, 3, sizeof(cl_mem), (void*)&d_mem_obj);
	ret = clSetKernelArg(kernel, 4, sizeof(cl_mem), (void*)&e_mem_obj);

	size_t global_item_size = words;
	size_t local_item_size = 1;
	cl_event event;

	ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);
	ret = clFinish(command_queue);
	ret = clEnqueueReadBuffer(command_queue, e_mem_obj, CL_TRUE, 0, words*sizeof(int), n, 0, NULL, NULL);

	int count = 0;

	for (int i = 0; i < words; ++i)
	{
		if(n[i] == 1)
			count++;
	}

	printf("String %s is occurring %d times\n", key, count);
	fflush(stdout);

	ret = clFlush(command_queue);
	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);
	ret = clReleaseMemObject(a_mem_obj);
	ret = clReleaseMemObject(b_mem_obj);
	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);
	return 0;
}
