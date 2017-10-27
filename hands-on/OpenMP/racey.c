//
// This is a very simple program we can use to play with tasks.
//
// The program prints 
//
//     I think race cars are fun.
//
//  the idea is to insert tasks so it will print either: 
//
//     I think race cars are fun.
//     I think car races are fun.
//
//  This is a race condition since depending on how the
//  threads are scheduled, you will get a different answer.
//  We aren't writing any variables.  Hence this is not
//  a data race and the program is legal.
//

#include <stdio.h>
#include <omp.h>

int main()
{

   printf("I think");

   #pragma omp parallel
   {
     #pragma omp single
     {
       #pragma omp task
       printf(" race");
       #pragma omp task
       printf(" car");
     }
   }
   printf("s are fun!\n");
 
}
