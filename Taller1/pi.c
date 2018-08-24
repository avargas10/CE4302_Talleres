/*

This program will numerically compute the integral of

                  4/(1+x*x) 
				  
from 0 to 1. 
				 
History: Written by Tim Mattson, 11/99.

#-----------------------------------------------------

Modified by JGG 
Modified by Andres Vargas August 2018
#--------------------------------------------------------

*/

#include <stdio.h>
#include <omp.h>
/* 
Numeros de pasos
-100000000
-1000000
-10000
-500
-100
-10
-1

*/
static long num_steps = 1;
double step;
int main ()
{
	int i, nprocs;
	double x, pi, sum = 0.0;
	double start_time, run_time;

	step = 1.0/(double) num_steps;

	/*start timer */
	start_time = omp_get_wtime();

	//Inicio de zona  paralelizable
	for (i=1;i<= num_steps; i++){
	x = (i-0.5)*step;
	sum = sum + 4.0/(1.0+x*x);
	}
	//Final Zona paralelizable
	
	pi = step * sum;
	run_time = omp_get_wtime() - start_time;
	printf("\n pi is %f in %f seconds \n",pi,run_time);
	
}	  



