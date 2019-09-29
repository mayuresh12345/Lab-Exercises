#include <stdio.h>
#include <CL/cl.h>
#include <stdlib.h>

//Max source size of the kernel string
#define MAX_SOURCE_SIZE (0x100000)

int main(void){

	// Create the two input vectors
	int LIST_SIZE;
	printf("Enter how many elements:");
	scanf("%d",&LIST_SIZE);

	//Initialize the input vectors
	int *A = (int*) malloc (sizeof (int) * LIST_SIZE);
	printf("Enter the elements: \n");
	for(int i = 0; i < LIST_SIZE; i++){
		scanf("%d",A+i);
	}

	// Load the kernel source code into the array source_str
	FILE *fp;
	char *source_str1, *source_str2;
	size_t source_size1, source_size2;
	fp = fopen("oddEven.cl", "r");
	if (!fp){
		fprintf(stderr, "Failed to load kernel.\n");
		getchar();
		exit(1);
	}
	source_str1 = malloc(MAX_SOURCE_SIZE);
	source_size1 = fread( source_str1, 1, MAX_SOURCE_SIZE, fp);
	fclose(fp);
	fp = fopen("evenOdd.cl", "r");
	if (!fp){
		fprintf(stderr, "Failed to load kernel.\n");
		getchar();
		exit(1);
	}
	source_str2 = malloc(MAX_SOURCE_SIZE);
	source_size2 = fread( source_str2, 1, MAX_SOURCE_SIZE, fp);
	fclose( fp );

	// Get platform and device information
	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;

	cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_GPU, 1,&device_id,&ret_num_devices);

	// Create an OpenCL context
	cl_context context = clCreateContext( NULL, 1, &device_id, NULL, NULL,&ret);

	// Create a command queue
	cl_command_queue command_queue = clCreateCommandQueue(context, device_id, NULL, &ret);

	// Create memory buffers on the device for each vector A, B and C
	cl_mem a_mem_obj = clCreateBuffer(context,CL_MEM_READ_WRITE,LIST_SIZE * sizeof(int), NULL, &ret);

	// Create a program from the kernel source
	cl_program program1 = clCreateProgramWithSource(context, 1, (const char**)&source_str1, (const size_t *)&source_size1, &ret);
	cl_program program2 = clCreateProgramWithSource(context, 1, (const char**)&source_str2, (const size_t *)&source_size2, &ret);

	// Build the program
	ret = clBuildProgram(program1, 1, &device_id, NULL, NULL, NULL);
	ret = clBuildProgram(program2, 1, &device_id, NULL, NULL, NULL);

	// Create the OpenCL kernel object
	cl_kernel kernel1 = clCreateKernel(program1, "oddEven", &ret);
	cl_kernel kernel2 = clCreateKernel(program2, "evenOdd", &ret);

	// Set the arguments of the kernel
	ret = clSetKernelArg(kernel1, 0, sizeof(cl_mem), (void *)&a_mem_obj);
	ret = clSetKernelArg(kernel2, 0, sizeof(cl_mem), (void *)&a_mem_obj);

	// Execute the OpenCL kernel on the array
	size_t global_item_size = LIST_SIZE;
	size_t local_item_size = 1;

	//Write to Buffer
	ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE,0,LIST_SIZE * sizeof(int), A, 0, NULL, NULL);


	//Execute the kernel on the device
	for(int i = 0; i <= LIST_SIZE/2; i++){
		ret = clEnqueueNDRangeKernel(command_queue, kernel1, 1, NULL,&global_item_size, &local_item_size, 0, NULL, NULL);
		ret = clFinish(command_queue);
		ret = clEnqueueNDRangeKernel(command_queue, kernel2, 1, NULL,&global_item_size, &local_item_size, 0, NULL, NULL);
		ret = clFinish(command_queue);
	}

	ret = clEnqueueReadBuffer(command_queue, a_mem_obj, CL_TRUE, 0,LIST_SIZE* sizeof(int), A, 0, NULL, NULL);

	// Display the result to the screen
	printf("Sorted Order : \n");
	for(int i = 0; i < LIST_SIZE; i++)
	printf("%d\t", A[i]);

	// Clean up
	ret = clFlush(command_queue);
	ret = clReleaseKernel(kernel1);
	ret = clReleaseKernel(kernel2);
	ret = clReleaseProgram(program1);
	ret = clReleaseProgram(program2);
	ret = clReleaseMemObject(a_mem_obj);
	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);
	free(A);
	getchar();
	return 0;
}

