/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 20:10:00 by aalliot           #+#    #+#             */
/*   Updated: 2015/02/03 20:10:03 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		rainbow_color(double pos, t_all *all)
{
	t_rbow	rbow;

	if (pos > 1.0)
		pos = (pos - (int)pos) == 0.0 ? 1.0 : (pos - (int)pos);
	rbow.nmax = 6;
	rbow.m = rbow.nmax * pos;
	rbow.n = (int)rbow.m;
	rbow.f = rbow.m - rbow.n;
	rbow.t = (int)(rbow.f * 255);
	if (rbow.n == 0)
		rbow.c = ft_rgb_to_color(0, rbow.t, 0);
	else if (rbow.n == 1)
		rbow.c = ft_rgb_to_color(255 - rbow.t, 255, 0);
	else if (rbow.n == 2)
		rbow.c = ft_rgb_to_color(0, 255, rbow.t);
	else if (rbow.n == 3)
		rbow.c = ft_rgb_to_color(0, 255 - rbow.t, 255);
	else if (rbow.n == 4)
		rbow.c = ft_rgb_to_color(rbow.t, 0, 255);
	else if (rbow.n == 5)
		rbow.c = ft_rgb_to_color(255, 0, 255 - rbow.t);
	else
		rbow.c = ft_rgb_to_color(0, 0, 0);
	all->img.clrline = ft_color_to_int(rbow.c);
}

void		color_fill(int t, t_color *color, t_pwr p)
{
	if (0 <= t && t < 60)
		color->r = -0.00018094381200185858 * p.t3 + 0.011590107725603593 * p.t2
		+ 0.1833371893610704 * t + 52;
	else if (60 <= t && t < 104)
		color->r = -0.0013237924865831855 * p.t3 + 0.2778533094812168 * p.t2 +
		-19.741144901609974 * t + 535.1359570661889;
	else
		color->r = 0;
	if (0 <= t && t < 16)
		color->g = 0;
	else if (16 <= t && t < 210)
		color->g = 0.000039395117125758106 * p.t2 + 1.2892809386010193 * t +
		-19.639683498985086;
	else
		color->g = 255;
	if (0 <= t && t < 129)
		color->b = 0;
	else if (129 <= t && t < 202)
		color->b = 0.00019290123456790166 * p.t3 + -0.0928819444444442 * p.t2 +
		18.07638888888897 * t + -1196.3046875;
	else
		color->b = 255;
}

UINT		rainbow_cycle(int t)
{
	t_pwr	pwr;
	t_color	color;

	pwr.t2 = t * t;
	pwr.t3 = pwr.t2 * t;
	color_fill(t, &color, pwr);
	return (ft_color_to_int(color));
}

void		color_filter(t_all *all, int *i, t_pos *pt)
{
	t_color		colors[4];
	t_color		final;

	colors[0] = ft_int_to_color(i[(int)pt->x - 1 + ((int)pt->y * WIN_SZ_X)]);
	colors[1] = ft_int_to_color(i[(int)pt->x + (((int)pt->y + 1) * WIN_SZ_X)]);
	colors[2] = ft_int_to_color(i[(int)pt->x + 1 + ((int)pt->y * WIN_SZ_X)]);
	colors[3] = ft_int_to_color(i[(int)pt->x + (((int)pt->y - 1) * WIN_SZ_X)]);
	final.r = (colors[0].r + colors[1].r + colors[2].r + colors[3].r) / 4;
	final.g = (colors[0].g + colors[1].g + colors[2].g + colors[3].g) / 4;
	final.b = (colors[0].b + colors[1].b + colors[2].b + colors[3].b) / 4;
	all->img.clrline = ft_color_to_int(final);
}

void		color_renorm(t_all *all, t_pos pt)
{
	pt.x = 1;
	while (pt.x < WIN_SZ_X - 1)
	{
		pt.y = 1;
		while (pt.y < WIN_SZ_Y - 1)
		{
			color_filter(all, (int*)all->img.data, &pt);
			ft_put_pxl(all, &pt);
			pt.y++;
		}
		pt.x++;
	}
}
