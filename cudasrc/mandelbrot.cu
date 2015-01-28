
#include <stdlib.h>
#include <cuda.h>
#include <stdio.h>
# define WIN_SZ_X 1024
# define WIN_SZ_Y 1024

__global__ void			mandelbrot(int	*d_i, double offx, double offy, double zoom, int ite_max, int winszx, int winszy)
{
	double	x1;
	double	y1;
	double	c_r;
	double	c_i;
	double	z_r;
	double	z_i;
	double	tmp;
	int		i;
	int		row;  // WIDTH
	int		col;  // HEIGHT
	int		index;
	row = blockIdx.y * blockDim.y + threadIdx.y;
	col = blockIdx.x * blockDim.x + threadIdx.x;
	index = row * winszx + col;
	if(col >= winszx || row >= winszy)
		return;

	x1 = -2.1;
	y1 = -1.2;
	c_r = (((double)col + offx) / zoom) + x1;
	c_i = (((double)row + offy) / zoom) + y1;
	z_r = 0.0;
	z_i = 0.0;
	i = 0;
	while((z_r * z_r + z_i * z_i) < 4 && i < ite_max)
	{
		tmp = z_r;
		z_r = (z_r * z_r) - (z_i * z_i) + c_r;
		z_i = (2 * tmp * z_i) + c_i;
		i++;
	}
	d_i[index] = i;
}

extern "C" void			call_mandelbrot(int *i, double offx, double offy, double zoom, int ite_max, int winszx, int winszy)
{
	int		*d_i;
	int		size;
	dim3	block_size(16, 16);
	dim3	grid_size(WIN_SZ_X / block_size.x, WIN_SZ_Y / block_size.y);

	size = WIN_SZ_Y * WIN_SZ_X * sizeof(int);
	cudaMalloc((void **)&d_i, size);
	mandelbrot<<<grid_size,block_size>>>(d_i, offx, offy, zoom, ite_max, winszx, winszy);

	cudaMemcpy(i, d_i, size, cudaMemcpyDeviceToHost);
	cudaFree(d_i);
}
