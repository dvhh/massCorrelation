BIN := ../bin

ALL :=	$(BIN)/massCorrelation \
	$(BIN)/massCorrelationMatrix \
	$(BIN)/massCorrelationThread \
	$(BIN)/massCorrelationNone \
	$(BIN)/compareBin 

ifneq ($(shell which nvcc),)
ALL +=	$(BIN)/massCorrelationGPU \
	$(BIN)/massCorrelationMatrixGpu 
endif

WARNINGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
            -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
            -Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
            -Wuninitialized -Wstrict-prototypes -Wconversion 

CFLAGS += $(WARNINGS) -std=c99 -D_GNU_SOURCE -D_POSIX_C_SOURCE=200809L -g -O3 
NVCCFLAGS += 
.PHONY : all clean

%.o : %.cu 
	nvcc -arch compute_20 --ptxas-options=-v --compiler-options "-O2" -c $^ -o $@

all : $(ALL)

clean :
	rm $(ALL) *.o

$(BIN)/massCorrelation : massCorrelation.o correlationCPU.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

$(BIN)/massCorrelationNone : massCorrelation.o correlationNone.o
	$(CC) $(CFLAGS) -o $@ $^ 

$(BIN)/massCorrelationCUDA : massCorrelation.o correlationCUDA.o
	$(CC) $(CFLAGS) -o $@ $^ -lm -L/usr/local/cuda/lib64 -lcudart

#correlationGPU.o : correlationGPU.cu
#	nvcc -arch compute_20 --ptxas-options=-v --compiler-options "-O2" -c $^ -o $@

$(BIN)/massCorrelationMatrix : massCorrelation.o correlationMatrixCpu.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

#correlationMatrixGpu.o : correlationMatrixGpu.cu
#	nvcc -arch compute_20 --ptxas-options=-v --compiler-options "-O2" -c $^ -o $@

$(BIN)/massCorrelationMatrixCUDA : massCorrelation.o correlationMatrixCUDA.o
	$(CC) $(CFLAGS) -o $@ $^ -lm -L/usr/local/cuda/lib64 -lcudart

$(BIN)/massCorrelationThread : massCorrelation.o correlationCPUThreads.o threadPool.o ringBuffer.o
	$(CC) $(CFLAGS) -o $@ $^ -lm -lpthread

$(BIN)/compareBin : compareBin.o
	$(CC) $(CFLAGS) -o $@ $^ -lm
correlationOMP.o : correlationOMP.c
	$(CC) $(CFLAGS) -c -fopenmp -o $@ $^ 

$(BIN)/massCorrelationOMP : massCorrelation.o correlationOMP.o
	$(CC) $(CFLAGS) -fopenmp -o $@ $^ -lm
