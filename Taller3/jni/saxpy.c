#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <arm_neon.h>
#include <stdint.h>
#define SIZE 100000
#define MAX 100
#define MIN -50
#define aData 10
#define bData 12
#define threads 8

void saxpyParallel(int size,int16_t *vectorA, int16_t *vectorX,int16_t *vectorB){
	printf("----------------------SAXPY----------------------\n\n");
  int16x4_t vecx;
  int16x4_t veca;
  int16x4_t vecb;
  int16x4_t res = vdup_n_s16(0);
  omp_set_num_threads(threads);
	#pragma omp parallel
  { 
         #pragma omp for
         for (int n = 0; n<size; n += 4)
         {
              /* load 4 values in parallel from the array */
              vecx = vld1_s16(vectorX+n);
              vecb = vld1_s16(vectorB+n);
              veca = vld1_s16(vectorA+n);
              res =  vmla_s16(vecb,vecx,veca);
              vectorB[n] = vget_lane_s16(res,0);
              vectorB[n+1] = vget_lane_s16(res,1);
              vectorB[n+2] = vget_lane_s16(res,2);
              vectorB[n+3] = vget_lane_s16(res,3);  
              /* increment the array pointer to the next element */
          }

  }
}

void saxpySerial(int n,int16_t *a, int16_t *vectorX,int16_t *vectorY){
  printf("--------------------------------------------------\n");
   for (int i = 0; i < n; ++i)
   {
      vectorY[i] = a[i]*vectorX[i]+vectorY[i];
   }
}

void filArray(int16_t *array,int size){
      for (int i = 0; i < size; ++i)
    	{
    		array[i]=i;
    	}
}
void filConstants(int16_t *a,int16_t *b,int size){
      for (int i = 0; i < size; ++i)
      {
        a[i]=aData;
        b[i]=bData;
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
  int16_t (*_Xarray) [SIZE];
  int16_t (*b) [SIZE];
  int16_t (*a) [SIZE];
  
  //Get memory space
  _Xarray = malloc(SIZE*sizeof(int16_t));
  a = malloc(SIZE*sizeof(int16_t));
  b = malloc(SIZE*sizeof(int16_t));
  
  //FIll the arrays
  filArray(*_Xarray,SIZE);
  filConstants(*a,*b,SIZE);

  //Parallel saxpy
  start_time = omp_get_wtime();
  saxpyParallel(SIZE,*a,*_Xarray,*b);
  run_time = omp_get_wtime() - start_time;
  printf("|   Parallel Run time = %f for %d size  |\n\n", run_time, SIZE);

  //Serial saxpy
  start_time = omp_get_wtime();
  saxpySerial(SIZE,*a,*_Xarray,*b);
  run_time = omp_get_wtime() - start_time;
  printf("|   Serial Run time = %f for %d size    |\n\n", run_time, SIZE);
  
  //Free the memory
  free(_Xarray);
  free(a);
  free(b);
  
  return 0;
}