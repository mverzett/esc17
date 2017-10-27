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
const double epsilon = 0.00001;

inline double eval(double x) {
  return 1.0/(1.0+x*x);
}

double area(double xmin, double xmax, double ymin, double ymax) {
  double r2 = xmax*xmax+ymax*ymax;
  bool c4 = (r2 <= 1);

  double Dx = (xmax - xmin);
  if(c4) return Dx*(ymax - ymin);
  double r1 = xmin*xmin+ymin*ymin;
  bool c1 = (r1 <= 1);
  if(!c1) return 0.;
  if(((xmax - xmin) < epsilon) || ((ymax - ymin) < epsilon)) return (Dx*(ymax - ymin))/2;

  double xmid = (xmax + xmin)*0.5;
  double ymid = (ymax + ymin)*0.5;
  double sum0 = 0, sum1 = 0;
  //bool spawn = Dx > 1./8.;
  //#pragma omp task default(none) firstprivate(xmin,xmid,xmax,ymin,ymid) shared(sum0) if(spawn)
  {
    double partial = area(xmin,xmid,ymin,ymid);
    partial += area(xmid,xmax,ymin,ymid);
    sum0 = partial;
  }
  //#pragma omp task default(none) firstprivate(xmin,xmid,xmax,ymid,ymax) shared(sum1) if(spawn)
  {
  double partial = area(xmin,xmid,ymid,ymax);
  partial += area(xmid,xmax,ymid,ymax);
  sum1 = partial;
  }
  //#pragma omp taskwait
  return sum0+sum1;
}

int main ()
{
  int i;
  double pi, sum = 0.0;
  double start_time, run_time;
        	 
  start_time = omp_get_wtime();
  //#pragma omp parallel 
  {
    //#pragma omp single 
    {
      pi = 4*area(0, 1., 0., 4.);
    }
  }
  run_time = omp_get_wtime() - start_time;
  printf("\n pi is %lf in %lf seconds\n ", pi, run_time);
}	  





