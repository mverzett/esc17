/*
**  function: Matrix Multiplication ... three loop, ijk case
**            where ijk defines the order of the loops
**
**  HISTORY: Written by Tim Mattson, July 2012. 
*/
#include "mm_utils.h"

void mm_ijk(int Ndim, int Mdim, int Pdim, TYPE *A, TYPE *B, TYPE *C){
  TYPE BT[Mdim*Pdim];  
  #pragma omp parallel for
  for (int j=0; j<Mdim; j++) { 
    for(int k=0;k<Pdim;k++) {  
      B[j*Pdim+k] = *(B+(k*Mdim+j));
    } 
  } 

  #pragma omp parallel for
  for (int i=0; i<Ndim; i++){ //loop on A rows
    for (int j=0; j<Mdim; j++){ //loop on B columns
      TYPE tmp[4] = {0};
      for(int k=0;k<Pdim;k += 4){ //loop on common element
	int a_idx = i*Pdim+k;
	int b_idx = j*Pdim+k;
	for(int h=0; h<4; h++) {
	/* C(i,j) = sum(over k) A(i,k) * B(k,j) */
	  tmp[h] += A[a_idx+h] * BT[b_idx+h];
	}
      }      
      *(C+(i*Mdim+j)) += tmp[0] + tmp[1] + tmp[2] + tmp[3];
    }
  }
}
