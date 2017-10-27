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
const double epsilon = 1e-8;

double area(double xmin, double xmax) {
  double delta = xmax - xmin;
  double x = (xmax + xmin)/2.;
  if(delta < epsilon) return delta*(4.0/(1.0+x*x));

  double a1 = 0, a2 = 0;
  #pragma omp task shared(a1) firstprivate(xmin,delta)
  a1 = area(xmin, xmin+delta/2.);
  #pragma omp task shared(a2) firstprivate(xmin,delta,xmax)
  a2 = area(xmin+delta/2., xmax);
  #pragma omp taskwait
  return a1 + a2;
}

int main ()
{
  int i;
  double pi, sum = 0.0;
  double start_time, run_time;
        	 
  start_time = omp_get_wtime();
#pragma omp parallel 
  {
#pragma omp single 
    {
      pi = area(0, 1.);
    }
  }
  run_time = omp_get_wtime() - start_time;
  printf("\n pi is %lf in %lf seconds\n ", pi, run_time);
}	  





