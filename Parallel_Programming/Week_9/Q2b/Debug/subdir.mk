################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CU_SRCS += \
../column_computedBy_oneThread.cu 

OBJS += \
./column_computedBy_oneThread.o 

CU_DEPS += \
./column_computedBy_oneThread.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cu
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/bin/nvcc -G -g -O0 -gencode arch=compute_30,code=sm_30  -odir "." -M -o "$(@:%.o=%.d)" "$<"
	/usr/bin/nvcc -G -g -O0 --compile --relocatable-device-code=false -gencode arch=compute_30,code=compute_30 -gencode arch=compute_30,code=sm_30  -x cu -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


