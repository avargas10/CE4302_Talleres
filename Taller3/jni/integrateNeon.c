
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <arm_neon.h>
#include <stdint.h>
#define threads 8
#define SIZE 400000

float f(float x)
{
    float a=1/(1+x*x);    //write the function whose definite integral is to be calcuated here
    return a;
}

void calcIntegralSerial(float a,float b,int n,float *x, float* y,float h){
    float sum = 0,integral;
                          //get the width of the subintervals
    for (int i=0;i<n+1;i++)
    {                        //loop to evaluate x0,...xn and y0,...yn
        x[i]=a+i*h;                //and store them in arrays
        y[i]=f(x[i]);
    }
    for (int i=1;i<n;i+=2)
    {
        sum=sum+4.0*y[i];                //loop to evaluate 4*(y1+y3+y5+...+yn-1)
    }
    for (int i=2;i<n-1;i+=2)
    {
        sum=sum+2.0*y[i];                /*loop to evaluate 4*(y1+y3+y5+...+yn-1)+
                                        2*(y2+y4+y6+...+yn-2)*/ 
    }
    integral=h/3.0*(y[0]+y[n]+sum);    //h/3*[y0+yn+4*(y1+y3+y5+...+yn-1)+2*(y2+y4+y6+...+yn-2)]
    
    printf("|   The definite integral  is  = %f   |\n\n", integral);
    
} 

void calcIntegralParallelReduction(float a,float b,int n,float *x, float* y,float h){
    float sum = 0,integral;
                              //get the width of the subintervals
    omp_set_num_threads(threads); 
    #pragma omp parallel 
    {   

        #pragma omp for
        
            for (int i=0;i<n+1;i++)
            {                        //loop to evaluate x0,...xn and y0,...yn
                x[i]=a+i*h;                //and store them in arrays
                y[i]=f(x[i]);
            }

        #pragma omp for reduction(+:sum)
        for (int i=1;i<n;i+=2)
        {
            sum=sum+4.0*y[i];                //loop to evaluate 4*(y1+y3+y5+...+yn-1)
        }
        #pragma omp for reduction(+:sum)
        for (int i=2;i<n-1;i+=2)
        {
            sum=sum+2.0*y[i];                /*loop to evaluate 4*(y1+y3+y5+...+yn-1)+
                                            2*(y2+y4+y6+...+yn-2)*/ 
        }
    }
  
    integral=h/3.0*(y[0]+y[n]+sum);    //h/3*[y0+yn+4*(y1+y3+y5+...+yn-1)+2*(y2+y4+y6+...+yn-2)]
    
    printf("|   The definite integral  is  = %f   |\n\n", integral);
    
} 

void calcIntegralParallel(float a,float b,int n,float *x, float* y,float h){
    float sum = 0,integral;
                         //get the width of the subintervals
    //float16x8_t vld1q_f16(__fp16 ); 
    omp_set_num_threads(threads);
    #pragma omp parallel 
    {   

        #pragma omp for
        
            for (int i=0;i<n+1;i++)
            {                        //loop to evaluate x0,...xn and y0,...yn
                x[i]=a+i*h;                //and store them in arrays
                y[i]=f(x[i]);
            }

        #pragma omp for reduction(+:sum)
        for (int i=1;i<n;i+=2)
        {
            sum=sum+4.0*y[i];                //loop to evaluate 4*(y1+y3+y5+...+yn-1)
        }
        #pragma omp for reduction(+:sum)
        for (int i=2;i<n-1;i+=2)
        {
            sum=sum+2.0*y[i];                /*loop to evaluate 4*(y1+y3+y5+...+yn-1)+
                                            2*(y2+y4+y6+...+yn-2)*/ 
        }
    }
  
    integral=h/3.0*(y[0]+y[n]+sum);    //h/3*[y0+yn+4*(y1+y3+y5+...+yn-1)+2*(y2+y4+y6+...+yn-2)]
    
    printf("|   The definite integral  is  = %f   |\n\n", integral);
    
} 
int main()
{  
    double start_time, run_time; 
    int n,i;            //n is for subintervals and i is for loop
    float a,b,c,h;
    a = 1.0;
    b= 25.0;
    n=SIZE;
    //cout<<"\nEnter the no. of subintervals, \nn=";        //get the no. of subintervals
    //cin>>n;
    float (*x) [SIZE];
    float (*y) [SIZE];
    x = malloc((SIZE+1)*sizeof(float));
    y = malloc((SIZE+1)*sizeof(float));
    h=((b-a)/(float)n);
    printf("|   Limit A = %f   |\n\n", a);
    printf("|   Limit B = %f   |\n\n", b);
    printf("|   h = %f   |\n\n", h);
    
    printf("|   Serial Integral  |\n\n");
    start_time = omp_get_wtime();  
    calcIntegralSerial(a,b,n,*x,*y,h);
    run_time = omp_get_wtime() - start_time;
    printf("|   Serial Integral Run time = %f for %d size    |\n\n", run_time, SIZE);

    
    printf("|   Parallel Integral  |\n\n");
    start_time = omp_get_wtime();  
    calcIntegralParallel(a,b,n,*x,*y,h);
    run_time = omp_get_wtime() - start_time;
    printf("|   Parallel Integral Run time = %f for %d size    |\n\n", run_time, SIZE);


    printf("|   Parallel with reduction Integral  |\n\n");
    start_time = omp_get_wtime();  
    calcIntegralParallelReduction(a,b,n,*x,*y,h);
    run_time = omp_get_wtime() - start_time;
    printf("|   Parallel with reduction Integral Run time = %f for %d size    |\n\n", run_time, SIZE);
    return 0;
}




  