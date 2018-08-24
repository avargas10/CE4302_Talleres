#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <math.h>
#define iterations 100
int main() {
  int f  = factorial(5);
  printf("|   Factorial = %d|\n",f);
  return 0;
}

float getSen(float angule){
	float sum= 0.0;
	for (int i = 0; i < iterations; ++i)
	{
			sum = sum + pow(-1,i)*pow(angule/factorial(i),i);
	}
}

float getCos(float angule){
	float sum= 0.0;
	for (int i = 0; i < iterations; ++i)
	{
			sum = sum + pow(-1,i)*pow(angule/factorial(i),i);
	}
}

int factorial(int n){
	int res = 1;
	if(n==1 || n==0){

		return res;
	}
	
	else{

		for (int i = 1; i < n; ++i)
			{
				res = res*(i+1);	
			}
			return res;
	}
	
}