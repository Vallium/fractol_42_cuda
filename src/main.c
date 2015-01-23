/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 10:37:30 by aalliot           #+#    #+#             */
/*   Updated: 2015/01/16 10:37:32 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cudahead.h"
#include <stdlib.h>
#include <stdio.h>
#define N 512
#include "fractol.h"

t_color		ft_rgb_to_color(unsigned char r, unsigned char g, unsigned char b)
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

void		rainbow_color(double pos, t_all *all)
{
	t_color			c;
	unsigned char	nmax;
	double			m;
	int				n;
	double			f;
	unsigned char	t;

	if (pos > 1.0)
		pos = (pos - (int)pos) == 0.0 ? 1.0 : (pos - (int)pos);
	nmax = 6;
	m = nmax * pos;
	n = (int)m;
	f = m - n;
	t = (int)(f * 255);
	if (n == 0)
		c = ft_rgb_to_color(15, t, 0);
	else if (n == 1)
		c = ft_rgb_to_color(255 - t, 255, 0);
	else if (n == 2)
		c = ft_rgb_to_color(0, 255, t);
	else if (n == 3)
		c = ft_rgb_to_color(0, 255 - t, 255);
	else if (n == 4)
		c = ft_rgb_to_color(t, 0, 255);
	else if (n == 5)
		c = ft_rgb_to_color(0, 0, 255 - t);
	else
		c = ft_rgb_to_color(57, 22, 74);
	all->img.clrline = ft_color_to_int(c);
}

void		ft_put_pxl(t_all *all, t_pos *pt)
{
	if(pt->x > 0  && pt->x < WIN_SZ_X && pt->y > 0 && pt->y < WIN_SZ_Y)
		ft_memcpy(&all->img.data[((int)pt->x *4) + ((int)pt->y * all->img.sizeline)], &all->img.clrline, (size_t)sizeof(int));
}

void		cartridge(t_all *all)
{
	mlx_string_put(all->env.mlx, all->env.win, (WIN_SZ_X / 2) - 165, 20, 0xF65B0A,
	"                          FRACTOL                          ");
	mlx_string_put(all->env.mlx, all->env.win, (WIN_SZ_X / 2) - 165, 20, 0x98CD00,
	"+------------------------         ------------------------+");
}

void		frac_mandelbrot(t_all *all)
{
	t_pos	*pt;
	double	x1;
	double	y1;
	double	c_r;
	double	c_i;
	double	z_r;
	double	z_i;
	double	tmp;
	int		i;


	pt = (t_pos *)malloc(sizeof(t_pos));
	pt->x = 0;
	x1 = -2.1;
	y1 = -1.2;
	while (pt->x < WIN_SZ_X)
	{
		pt->y = 0;
		while (pt->y < WIN_SZ_Y)
		{
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
			rainbow_color((double)i / (double)all->ite_max, all);
			ft_put_pxl(all, pt);
			pt->y++;
		}
		pt->x++;
	}
	free(pt);
}

void		frac_julia(t_all *all)
{
	t_pos	*pt;
	float	x1;
	float	y1;
	float	z_r;
	float	z_i;
	float	tmp;
	int		i;

	pt = (t_pos *)malloc(sizeof(t_pos));
	x1 = -1.4;
	y1 = -1.2;
	pt->x = 0;
	while (pt->x < WIN_SZ_X)
	{
		pt->y = 0;
		while (pt->y < WIN_SZ_Y)
		{
			z_r = (float)(pt->x + all->off.x) / all->zoom + x1;
			z_i = (float)(pt->y + all->off.y) / all->zoom + y1;
			i = 0;
			while ((z_r * z_r + z_i * z_i) < 4 && i < all->ite_max)
			{
				tmp = z_r;
				z_r = (z_r * z_r) - (z_i * z_i) + all->c_r;
				z_i = (2 * tmp * z_i) + all->c_i;
				i++;
			}
			rainbow_color((double)i / (double)all->ite_max, all);
			ft_put_pxl(all, pt);
			pt->y++;
		}
		pt->x++;
	}
	free(pt);
}

//void		frac_buddhabrot(t_all *all)
//{
//	t_pos	*pt;
//	float	x1;
//	float	y1;
//	int		zoom;
//	int		ite_red;
//	int		ite_grn;
//	int		ite_blu;
//	int		ite_max;
//
//}

void		exit_prog(t_all *all)
{
	free(all->env.mlx);
	free(all->env.win);
	free(all);
	exit(0);
}

int			mouse_move(int x, int y, t_all *all)
{
	if(!all->f)
	{
		all->c_r = (float)(x - WIN_SZ_X / 2) / all->zoom;
		all->c_i = (float)(y - WIN_SZ_Y / 2) / all->zoom;
		all->re = 1;
	}
	return (0);
}

void		choose_frac(t_all *all)
{
	if (all->frac_no == 1)
		frac_mandelbrot(all);
	else if (all->frac_no == 2)
		frac_julia(all);
}

int			loop_hook(t_all *all)
{
	if(all->re)
	{
		if (all->re == -1)
			exit_prog(all);
		ft_bzero(all->img.data, WIN_SZ_X * WIN_SZ_Y * 4);
		//frac_mandelbrot(all);
		//frac_julia(all);
		choose_frac(all);
		mlx_put_image_to_window(all->env.mlx, all->env.win, all->img.img, 0, 0);
		//cartridge(all);
		all->re = 0;
	}
	return (0);
}

int			expose_hook(t_all *all)
{
	mlx_put_image_to_window(all->env.mlx, all->env.win, all->img.img, 0, 0);
	//cartridge(all);
	return(0);
}

int			key_hook(int keycode, t_all *all)
{
//	printf("<%d>\n", keycode);
	(void)all;
	if (keycode == 65307)
		all->re = -1;
	else if (keycode == 'a')//ite ++
	{
		all->ite_max += 5;
		all->re = 1;
	}
	else if (keycode == 'd')//ite --
	{
		all->ite_max -= 5;
		all->re = 1;
	}
	else if (keycode == 65362)//up
	{
		all->off.y += 10;
		all->re = 1;
	}
	else if (keycode == 65364)//down
	{
		all->off.y -= 10;
		all->re = 1;
	}
	else if (keycode == 65361)//left
	{
		all->off.x += 10;
		all->re = 1;
	}
	else if (keycode == 65363)//right
	{
		all->off.x -= 10;
		all->re = 1;
	}
	else if (keycode == 49)
	{
		all->frac_no = 1;
		all->re = 1;
	}
	else if (keycode == 50)
	{
		all->frac_no = 2;
		all->re = 1;
	}
	return (0);
}

int			mouse_hook(int button, int x, int y, t_all *all)
{
	(void)x;
	(void)y;
	(void)all;
	if (button == 4)
	{
		all->zoom *= ZOOM;
		all->off.x = (all->off.x + ((WIN_SZ_X - (WIN_SZ_X / ZOOM)) / 2) + (x - WIN_SZ_X / 2) * (1 - (1 / ZOOM))) * ZOOM;
		all->off.y = (all->off.y + ((WIN_SZ_Y - (WIN_SZ_Y / ZOOM)) / 2) + (y - WIN_SZ_Y / 2) * (1 - (1 / ZOOM))) * ZOOM;
		all->re = 1;
	}
	if (button == 5)
	{
		all->zoom /= ZOOM;
		all->off.x = all->off.x / ZOOM - ((WIN_SZ_X - (WIN_SZ_X / ZOOM)) / 2) / ZOOM - (x - WIN_SZ_X / 2) * (1 - (1 / ZOOM)) + ZOOM;
		all->off.y = all->off.y / ZOOM - ((WIN_SZ_Y - (WIN_SZ_Y / ZOOM)) / 2) / ZOOM - (y - WIN_SZ_Y / 2) * (1 - (1 / ZOOM)) + ZOOM;
		all->re = 1;
	}
	if (button == 1)
	{
		all->f = all->f ? 0 : 1;
		all->re = 1;
	}
	return (0);
}

int			main(void)
{
	t_all		*all;

	all = (t_all *)malloc(sizeof(t_all));
	all->env.mlx = mlx_init();
	all->env.win = mlx_new_window(all->env.mlx, WIN_SZ_X, WIN_SZ_Y, "Fractol");
	all->img.img = mlx_new_image(all->env.mlx, WIN_SZ_X, WIN_SZ_Y);
	all->img.data = mlx_get_data_addr(all->img.img, &all->img.bpp, &all->img.sizeline, &all->img.endian);
	all->img.clrline = 0xF65B0A;
	all->zoom = 300;
	all->off.x = 0;
	all->off.y = 0;
	all->ite_max = 100;
	all->frac_no = 1;
	all->re = 1;
	all->f = 0;

	mlx_hook(all->env.win, MotionNotify, PointerMotionMask, mouse_move, all);
	mlx_key_hook(all->env.win, key_hook, all);
	mlx_mouse_hook(all->env.win, mouse_hook, all);
	mlx_loop_hook(all->env.mlx, loop_hook, all);
	mlx_expose_hook(all->env.win, expose_hook, all);
	mlx_loop(all->env.mlx);
	return (0);
}
