/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 20:10:49 by aalliot           #+#    #+#             */
/*   Updated: 2015/02/03 20:10:56 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_color		ft_rgb_to_color(UCHAR r, UCHAR g, UCHAR b)
{
	t_color		color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

int			ft_color_to_int(t_color color)
{
	int		c;

	c = color.r;
	c = c << 8;
	c += color.g;
	c = c << 8;
	c += color.b;
	return (c);
}

t_color		ft_int_to_color(int i)
{
	t_color		c;

	c.b = i & 0xFF;
	i = i >> 8;
	c.g = i & 0xFF;
	i = i >> 8;
	c.r = i & 0xFF;
	return (c);
}

void		ft_put_pxl(t_all *all, t_pos *pt)
{
	int		i;
	UINT	color;

	color = all->img.clrline;
	i = pt->y * all->img.sizeline + pt->x * all->inc;
	all->img.data[i] = mlx_get_color_value(all->env.mlx, color);
	all->img.data[i + 1] = mlx_get_color_value(all->env.mlx, color >> 8);
	all->img.data[i + 2] = mlx_get_color_value(all->env.mlx, color >> 16);
}
