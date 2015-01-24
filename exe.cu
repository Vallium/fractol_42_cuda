#include <cuda.h>
#include <cuda_call.h>
#include <stdio.h>
__global__ void mandelbrot_2(unsigned int* a, unsigned int constw, unsigned int consth, float middlex,
                            float middley, float scale, unsigned int max)
{
  int row = blockIdx.y * blockDim.y + threadIdx.y;
  int col = blockIdx.x * blockDim.x + threadIdx.x;
  int index = row * constw + col;
  if(col >= constw || row >= consth) return;
    float ci = (row * scale - middley);
    float cr = (col * scale - middlex) ;
    float x = 0;
    float y = 0;
    float xq = 0;
    float yq = 0;
   unsigned int iteration = 0;
  while (iteration++ < max && (xq + yq) < 4)
  {
    y = 2 * x * y + ci;
    x = xq - yq + cr;
    xq = x * x;
    yq = y * y;
  }
  a[index] = iteration;
}


extern "C" void cuda_call_mandelbrot(unsigned int* a_h, unsigned int constw, unsigned int consth, float middlex,
                                    float middley, float scale, unsigned int max, unsigned int reset)
{
  static unsigned int *a_d = NULL;
  static size_t size = 0;
  static dim3 block_size(16, 16);
  static dim3 grid_size(constw / block_size.x + (constw - constw / block_size.x), consth / block_size.y + (consth - consth / block_size.y));
  if (!reset)
  {
    if (size == 0)
    {
      size = constw * consth * sizeof(unsigned int);
      cudaMalloc((void **) &a_d, size);
    }
   mandelbrot_2 <<< grid_size, block_size, 0 >>> ((unsigned int *)a_d, constw, consth, middlex, middley, scale, max);
   cudaMemcpy(a_h, a_d, size, cudaMemcpyDeviceToHost);
  }
  else
    cudaFree(a_d);
}
