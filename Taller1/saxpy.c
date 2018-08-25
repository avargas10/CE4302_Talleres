#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#define SIZE 2000
#define MAX 100
#define MIN -50
#define threads 8

void saxpyParallel(int n,int a, int *vectorX,int *vectorY){
	printf("----------------------SAXPY----------------------\n\n");
  omp_set_num_threads(threads);
	#pragma omp parallel
  { 
         #pragma omp for
         for (int i = 0; i < n; ++i)
      	 {
      	   	vectorY[i] = a*vectorX[i]+vectorY[i];
      	 }
  }
}

void saxpySerial(int n,int a, int *vectorX,int *vectorY){
  printf("--------------------------------------------------\n");
   for (int i = 0; i < n; ++i)
   {
      vectorY[i] = a*vectorX[i]+vectorY[i];
   }
}

void filArray(int *array,int size){
      for (int i = 0; i < size; ++i)
    	{
    		int n = getRandom();
    		//printf("Value = %d ", n);
    		array[i]=n;
    	}
}

int getRandom(){
	 return rand() % MAX + MIN;
}

void printArray(int *array1,int size){
	for (int i = 0; i < size; ++i)
	{
		printf("Value = %d at %d\n", array1[i], i);
	}
}

int main() {
  double start_time, run_time;
  //declare arrays
  int (*_Xarray) [SIZE];
  int (*_Yarray) [SIZE];
  
  //Get memory space
  _Xarray = malloc(SIZE*sizeof(int));
  _Yarray = malloc(SIZE*sizeof(int));
  
  //FIll the arrays
  filArray(*_Xarray,SIZE);
  filArray(*_Yarray,SIZE);

  //Parallel saxpy
  start_time = omp_get_wtime();
  saxpyParallel(SIZE,10,*_Xarray,*_Yarray);
  run_time = omp_get_wtime() - start_time;
  printf("|   Parallel Run time = %f for %d size  |\n\n", run_time, SIZE);

  //Serial saxpy
  start_time = omp_get_wtime();
  saxpySerial(SIZE,10,*_Xarray,*_Yarray);
  run_time = omp_get_wtime() - start_time;
  printf("|   Serial Run time = %f for %d size    |\n\n", run_time, SIZE);
  
  //Free the memory
  free(_Xarray);
  free(_Yarray);
  
  return 0;
}