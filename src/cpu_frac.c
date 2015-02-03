/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_frac.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 20:10:10 by aalliot           #+#    #+#             */
/*   Updated: 2015/02/03 20:10:12 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		color_frac(int i, t_all *all)
{
	if (all->color > 0)
	{
		if (i == all->ite_max)
			all->img.clrline = 0x151515;
		else
			all->img.clrline = all->colors[i & 255];
	}
	else
		rainbow_color(((double)i * 4.0) / (double)all->ite_max, all);
}

void		frac_calc(t_frac *frac, double c_r, double c_i, int ite_max)
{
	frac->d_r = frac->z_r * frac->z_r;
	frac->d_i = frac->z_i * frac->z_i;
	while ((frac->d_r + frac->d_i) < 4 && frac->i < ite_max)
	{
		frac->z_i = (2 * frac->z_r * frac->z_i) + c_i;
		frac->z_r = frac->d_r - frac->d_i + c_r;
		frac->d_r = frac->z_r * frac->z_r;
		frac->d_i = frac->z_i * frac->z_i;
		frac->i++;
	}
}

void		frac_mandelbrot(t_all *all)
{
	t_frac	frac;

	frac.pt.x = 0;
	frac.x1 = -2.1;
	frac.y1 = -1.2;
	while (frac.pt.x < WIN_SZ_X)
	{
		frac.pt.y = 0;
		frac.c_r = ((frac.pt.x + all->off.x) / all->zoom) + frac.x1;
		frac.c_i = ((frac.pt.y + all->off.y) / all->zoom) + frac.y1;
		while (frac.pt.y < WIN_SZ_Y)
		{
			frac.z_r = frac.c_r;
			frac.z_i = frac.c_i;
			frac.c_i += 1 / all->zoom;
			frac.i = 0;
			frac_calc(&frac, frac.c_r, frac.c_i, all->ite_max);
			color_frac(frac.i, all);
			ft_put_pxl(all, &frac.pt);
			frac.pt.y++;
		}
		frac.pt.x++;
	}
}

void		frac_julia(t_all *all)
{
	t_frac	frac;

	frac.x1 = -1.4;
	frac.y1 = -1.2;
	frac.pt.x = 0;
	while (frac.pt.x < WIN_SZ_X)
	{
		frac.pt.y = 0;
		while (frac.pt.y < WIN_SZ_Y)
		{
			frac.z_r = (frac.pt.x + all->off.x) / all->zoom + frac.x1;
			frac.z_i = (frac.pt.y + all->off.y) / all->zoom + frac.y1;
			frac.i = 0;
			frac_calc(&frac, all->c_r, all->c_i, all->ite_max);
			color_frac(frac.i, all);
			ft_put_pxl(all, &frac.pt);
			frac.pt.y++;
		}
		frac.pt.x++;
	}
}

void		frac_douady(t_all *all)
{
	t_frac	frac;

	frac.x1 = -1.4;
	frac.y1 = -1.2;
	frac.c_r = -0.123;
	frac.c_i = 0.745;
	frac.pt.x = 0;
	while (frac.pt.x < WIN_SZ_X)
	{
		frac.pt.y = 0;
		while (frac.pt.y < WIN_SZ_Y)
		{
			frac.z_r = (frac.pt.x + all->off.x) / all->zoom + frac.x1;
			frac.z_i = (frac.pt.y + all->off.y) / all->zoom + frac.y1;
			frac.i = 0;
			frac_calc(&frac, frac.c_r, frac.c_i, all->ite_max);
			color_frac(frac.i, all);
			ft_put_pxl(all, &frac.pt);
			frac.pt.y++;
		}
		frac.pt.x++;
	}
}
