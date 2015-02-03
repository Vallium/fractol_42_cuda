/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cudahead.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 16:08:27 by aalliot           #+#    #+#             */
/*   Updated: 2015/02/03 16:08:30 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <cuda.h>
#include <stdio.h>
# define WIN_SZ_X 1024
# define WIN_SZ_Y 1024

__global__ void		mandelbrot(int	*d_tab, double offx, double offy, double zoom, int ite_max, int winszx, int winszy)
{
	double	x1;
	double	y1;
	double	c_r;
	double	c_i;
	double	z_r;
	double	z_i;
	double	d_i;
	double	d_r;
	int		i;
	int		row;
	int		col;
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
	z_r = c_r;
	z_i = c_i;
	d_r = z_r * z_r;
	d_i = z_i * z_i;
	i = 0;
	while((d_r + d_i) < 4 && i < ite_max)
	{
		z_i = (2 * z_r * z_i) + c_i;
		z_r = d_r - d_i + c_r;
		d_r = z_r * z_r;
		d_i = z_i * z_i;
		i++;
	}
	d_tab[index] = i;
}

extern "C" void			call_mandelbrot(int *tab, double offx, double offy, double zoom, int ite_max, int winszx, int winszy)
{
	int		*d_tab;
	int		size;
	dim3	block_size(16, 16);
	dim3	grid_size(WIN_SZ_X / block_size.x, WIN_SZ_Y / block_size.y);

	size = WIN_SZ_Y * WIN_SZ_X * sizeof(int);
	cudaMalloc((void **)&d_tab, size);
	mandelbrot<<<grid_size,block_size>>>(d_tab, offx, offy, zoom, ite_max, winszx, winszy);

	cudaMemcpy(tab, d_tab, size, cudaMemcpyDeviceToHost);
	cudaFree(d_tab);
}
