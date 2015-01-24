
#include <stdlib.h>
#include <cuda.h>
#include <stdio.h>
#define N (2048 * 2048)
#define M 512

__global__ void			madelbrot(int	*d_i, t_pos *pt, t_all *all)
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
	int		idx;
	row = blockIdx.y * blockDim.y + threadIdx.y;
	col = blockIdx.x * blockDim.x + threadIdx.x;
	index = row * WIN_SZ_X + col;
	if(col >= WIN_SZ_X || row >= WIN_SZ_Y)
		return;

	x1 = -2.1;
	y1 = -1.2;
	c_r = (((double)pt->x + (double)all->off.x) / (double)all->zoom) + x1;
	c_i = (((double)pt->y + (double)all->off.y) / (double)all->zoom) + y1;
	z_r = 0.0;
	z_i = 0.0;
	i = 0;
	while((z_r * z_r + z_i * z_i) < 4 && i < all->ite_max)
	{
		tmp = z_r;
		z_r = (z_r * z_r) - (z_i * z_i) + c_r;
		z_i = (2 * tmp * z_i) + c_i;
		i++;
	}
	d_i[index] = i;
}

extern "C" void			call_mandelbrot(t_all *all)
{
	t_pos	*pt;
	int		i;
	int		*d_i;
	dim3	block_size(16, 16);
	dim3	grid_size(WIN_SZ_X / block_size.x, WIN_SZ_Y / block_size.y);

	size = WIN_SZ_Y * WIN_SZ_X * sizeof(int);
	i = 0;
	cudaMalloc((void **)&d_i, size);
	pt = (t_pos *)malloc(sizeof(t_pos));
	pt->x = 0;
	while (pt->x < WIN_SZ_X)
	{
		pt->y = 0;
		while (pt->y < WIN_SZ_X)
		{
			mandelbrot<<<grid_size,block_size>>>(d_i, pt, all);
			cudaMemcpy(&i, d_i, size, cudaMemcpyDeviceToHost);
			rainbow_color((double)i / (double)all->ite_max, all);
			ft_put_pxl(all, pt);
		}
	}
}
