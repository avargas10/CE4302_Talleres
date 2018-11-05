
//Simpson's 1/3rd Rule for Evaluation of Definite Integrals
#include<iostream>
#include<cmath>
#include <omp.h>
using namespace std;
double f(double x)
{
    double a=1/(1+x*x);    //write the function whose definite integral is to be calcuated here
    return a;
}

void calcIntegralSerial(double a,double b,int n,double *x, double* y,double h){
    double sum = 0,integral;
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
    
    cout<<"\nThe definite integral  is "<<integral<<endl;
    
} 

void calcIntegralParallelReduction(double a,double b,int n,double *x, double* y,double h){
    double sum = 0,integral;
                              //get the width of the subintervals
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
    
    cout<<"\nThe definite integral  is "<<integral<<endl;
    
} 

void calcIntegralParallel(double a,double b,int n,double *x, double* y,double h){
    double sum = 0,integral;
                             
    #pragma omp parallel 
    {   

        #pragma omp for
        
            for (int i=0;i<n+1;i++)
            {                        //loop to evaluate x0,...xn and y0,...yn
                x[i]=a+i*h;                //and store them in arrays
                y[i]=f(x[i]);
            }
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
    
    cout<<"\nThe definite integral  is "<<integral<<endl;
    
} 
int main()
{  
    double start_time, run_time; 
    cout.precision(4);        //set the precision
    cout.setf(ios::fixed);
    int n,i;            //n is for subintervals and i is for loop
    double a,b,c,h;
    cout<<"\nEnter the limits of integration,\n\nInitial limit,a= ";
    cin>>a;
    cout<<"\nFinal limit, b=";                //get the limits of integration
    cin>>b;
    cout<<"\nEnter the no. of subintervals, \nn=";        //get the no. of subintervals
    cin>>n;
    double *x,*y;
    x =  (double *) malloc((n+1)*sizeof(double));
    y = (double *) malloc((n+1)*sizeof(double));
    h=(b-a)/n;

    
    cout<<endl<<"Serial Integral"<<"\n"<<endl;
    start_time = omp_get_wtime();  
    calcIntegralSerial(a,b,n,x,y,h);
    run_time = omp_get_wtime() - start_time;
    cout<<"Serial Time: "<<run_time<<"\n"<<endl;

    
    cout<<endl<<"Parallel Integral"<<"\n"<<endl;
    start_time = omp_get_wtime();  
    calcIntegralParallel(a,b,n,x,y,h);
    run_time = omp_get_wtime() - start_time;
    cout<<"Parallel Time: "<<run_time<<"\n"<<endl;


    cout<<endl<<"Parallel with Reduction Integral"<<"\n"<<endl;;
    start_time = omp_get_wtime();  
    calcIntegralParallelReduction(a,b,n,x,y,h);
    run_time = omp_get_wtime() - start_time;
    cout<<"Parallel with reduction Time: "<<run_time<<"\n"<<endl;
    return 0;
}




  