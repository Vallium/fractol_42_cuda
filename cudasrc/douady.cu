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

__global__ void		douady(int	*d_tab, double offx, double offy, double zoom, int ite_max, int winszx, int winszy)
{
	double	x1;
	double	y1;
	double	c_r;
	double	c_i;
	double	z_r;
	double	z_i;
	double	tmp;
	int		i;
	int		row;
	int		col;
	int		index;
	row = blockIdx.y * blockDim.y + threadIdx.y;
	col = blockIdx.x * blockDim.x + threadIdx.x;
	index = row * winszx + col;
	if(col >= winszx || row >= winszy)
		return;

	x1 = -1.4;
	y1 = -1.2;
	c_r = -0.123;
	c_i = 0.745;
	z_r = (((double)col + offx) / zoom) + x1;
	z_i = (((double)row + offy) / zoom) + y1;
	i = 0;
	while((z_r * z_r + z_i * z_i) < 4 && i < ite_max)
	{
		tmp = z_r;
		z_r = (z_r * z_r) - (z_i * z_i) + c_r;
		z_i = (2 * tmp * z_i) + c_i;
		i++;
	}
	d_tab[index] = i;
}

extern "C" void		call_douady(int *tab, double offx, double offy, double zoom, int ite_max, int winszx, int winszy)
{
	int		*d_tab;
	int		size;
	dim3	block_size(16, 16);
	dim3	grid_size(WIN_SZ_X / block_size.x, WIN_SZ_Y / block_size.y);

	size = WIN_SZ_Y * WIN_SZ_X * sizeof(int);
	cudaMalloc((void **)&d_tab, size);
	douady<<<grid_size,block_size>>>(d_tab, offx, offy, zoom, ite_max, winszx, winszy);

	cudaMemcpy(tab, d_tab, size, cudaMemcpyDeviceToHost);
	cudaFree(d_tab);
}
