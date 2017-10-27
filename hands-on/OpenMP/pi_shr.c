/*

This program will numerically compute the integral of

                  4/(1+x*x) 
				  
from 0 to 1.  The value of this integral is pi -- which 
is great since it gives us an easy way to check the answer.

The is the original sequential program.  It uses the timer
from the OpenMP runtime library

History: Written by Tim Mattson, 11/99.

*/
#include <stdio.h>
#include <omp.h>
static long num_steps = 100000000;
double step;
const static int num_threads = 8;

int main ()
{
  printf("Starting");
  omp_set_num_threads(num_threads);
  //printf("\nI got %d threads\n", nthreads);
  double sum=0;

  step = 1.0/(double) num_steps;        	 
  double start_time, run_time;
  start_time = omp_get_wtime();
  
  #pragma omp parallel
  {
    int thread_id = omp_get_thread_num();
    int nthreads = omp_get_num_threads();
    int start = 1+thread_id*(num_steps/nthreads);
    int stop = 1+(thread_id+1)*(num_steps/nthreads);

    double x = 0.0;    
    double partial = 0.;
    if(thread_id == 0) printf("NThreads: %d", nthreads);
    for (int i=start; i<= stop; i++){
      x = (i-0.5)*step;
      partial += 4.0/(1.0+x*x);
    }
    #pragma omp critical
      sum += partial;
  }
  
  double pi = step*sum;
  run_time = omp_get_wtime() - start_time;
  printf("\n pi with %ld steps is %lf in %lf seconds\n ",num_steps,pi,run_time);
}	  





