
//#define TYPE double
#define TYPE float

#if (TYPE == double)
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
#endif

kernel void jacobi(
  const unsigned Ndim,
  global TYPE * A,
  global TYPE * b,
  global TYPE * xold,
  global TYPE * xnew)
{
  // Fill in the kernel program based on the provided
  // serial program
  const int i = get_global_id(0);
  TYPE xnew_i = (TYPE) 0.0;
  const int row = i;

  for (int j=0; j<Ndim;j++){
    xnew_i += A[row+j*Ndim]*xold[j];
  }  
  xnew_i -= A[row+i*Ndim]*xold[i];
  xnew_i  = (b[i]-xnew_i)/A[row+i*Ndim];
  xnew[i] = xnew_i;
}


// We provide the kernel to test for convergence.  Do not make any 
// changes to the code from her to the end of this file

kernel void convergence(
  global TYPE * xold,
  global TYPE * xnew,
  local TYPE * conv_loc,
  global TYPE * conv
  )
{
  size_t i = get_global_id(0);
  TYPE tmp;

  tmp = xnew[i] - xold[i];
  conv_loc[get_local_id(0)] = tmp * tmp;

  barrier(CLK_LOCAL_MEM_FENCE);

  for (int offset = get_local_size(0) / 2; offset > 0; offset /= 2)
  {
    if (get_local_id(0) < offset)
    {
      conv_loc[get_local_id(0)] += conv_loc[get_local_id(0) + offset];
    }
    barrier(CLK_LOCAL_MEM_FENCE);
  }
  if (get_local_id(0) == 0)
  {
    conv[get_group_id(0)] = conv_loc[0];
  }
}
