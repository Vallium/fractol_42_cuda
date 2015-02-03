/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpu_frac.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 20:10:19 by aalliot           #+#    #+#             */
/*   Updated: 2015/02/03 20:10:21 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		cuda_mandelbrot(t_all *all)
{
	t_pos		pt;
	int			o;

	o = 0;
	call_mandelbrot(all->tab, all->off.x, all->off.y, all->zoom, all->ite_max,
	WIN_SZ_X, WIN_SZ_Y);
	pt.y = 0;
	while (pt.y < WIN_SZ_Y)
	{
		pt.x = 0;
		while (pt.x < WIN_SZ_X)
		{
			color_frac(all->tab[o], all);
			ft_put_pxl(all, &pt);
			pt.x++;
			o++;
		}
		pt.y++;
	}
	if (all->filter > 0)
		color_renorm(all, pt);
}

void		cuda_julia(t_all *all)
{
	t_pos		pt;
	int			o;

	call_julia(all->tab, all->off.x, all->off.y, all->zoom, all->ite_max,
	WIN_SZ_X, WIN_SZ_Y, all->c_i, all->c_r);
	pt.y = 0;
	o = 0;
	while (pt.y < WIN_SZ_Y)
	{
		pt.x = 0;
		while (pt.x < WIN_SZ_X)
		{
			color_frac(all->tab[o], all);
			ft_put_pxl(all, &pt);
			pt.x++;
			o++;
		}
		pt.y++;
	}
	if (all->filter > 0)
		color_renorm(all, pt);
}

void		cuda_douady(t_all *all)
{
	t_pos		pt;
	int			o;

	o = 0;
	call_douady(all->tab, all->off.x, all->off.y, all->zoom, all->ite_max,
	WIN_SZ_X, WIN_SZ_Y);
	pt.y = 0;
	while (pt.y < WIN_SZ_Y)
	{
		pt.x = 0;
		while (pt.x < WIN_SZ_X)
		{
			color_frac(all->tab[o], all);
			ft_put_pxl(all, &pt);
			pt.x++;
			o++;
		}
		pt.y++;
	}
	if (all->filter > 0)
		color_renorm(all, pt);
}
