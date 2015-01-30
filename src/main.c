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
		c = ft_rgb_to_color(0, t, 0);
	else if (n == 1)
		c = ft_rgb_to_color(255 - t, 255, 0);
	else if (n == 2)
		c = ft_rgb_to_color(0, 255, t);
	else if (n == 3)
		c = ft_rgb_to_color(0, 255 - t, 255);
	else if (n == 4)
		c = ft_rgb_to_color(t, 0, 255);
	else if (n == 5)
		c = ft_rgb_to_color(255, 0, 255 - t);
	else
		c = ft_rgb_to_color(0, 0, 0);
	all->img.clrline = ft_color_to_int(c);
}

UINT		rainbow_cycle(int t)
{
	float	t1;
	float	t2;
	float	t3;
	float	b;
	float	r;
	float	g;
	UINT	ret;

	t1 = (float)t;
	t2 = t1 * t1;
	t3 = t2 * t1;
	r = 0;
	if (0 <= t && t < 209)
		g = 0.003528670055615052 * t2 + 0.687812343037689 * t +
		24.999999999999996;
	else
		g = 255;
	if (0 <= t && t < 87)
		b = 0;
	else if (87 <= t && t < 183)
		b = 0.00006248820977174108 * t3 + -0.02397391327781806 * t2 +
		5.55881690112377 * t + -340.30719439728364;
	else
		b = 255;
	ret = ((UINT)r << 16) | ((UINT)g << 8 & 0x00FF00) | ((UINT)b & 0x0000FF);
	return (ret);
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

void		cartridge(t_all *all)
{
	mlx_string_put(all->env.mlx, all->env.win, (WIN_SZ_X / 2) - 165, 20, \
	0xF65B0A, "                          FRACTOL                         ");
	mlx_string_put(all->env.mlx, all->env.win, (WIN_SZ_X / 2) - 165, 20, \
	0x98CD00, "+------------------------         -----------------------+");
	mlx_string_put(all->env.mlx, all->env.win, 10, 30, 0xF65B0A, all->name);
	if (!all->cuda_frac)
		mlx_string_put(all->env.mlx, all->env.win, 10, 50, 0xF65B0A,\
			"CUDA Parallel Computing Architecture : OFF");
	else
		mlx_string_put(all->env.mlx, all->env.win, 10, 50, 0xF65B0A,\
			"CUDA Parallel Computing Architecture : ON");
	mlx_string_put(all->env.mlx, all->env.win, 10, 70, 0xF65B0A,\
		"Number of iterations =");
	mlx_string_put(all->env.mlx, all->env.win, 150, 70, 0xF65B0A,\
		ft_itoa(all->ite_max));
	mlx_string_put(all->env.mlx, all->env.win, 10, 90, 0xF65B0A,\
		"Iteration +/- 200: a/d .");
	mlx_string_put(all->env.mlx, all->env.win, 10, 110, 0xF65B0A,\
		"Navigation : Arrows .");
	mlx_string_put(all->env.mlx, all->env.win, 10, 130, 0xF65B0A,\
		"Zoom : Scroll Mouse .");
	mlx_string_put(all->env.mlx, all->env.win, 10, 150, 0xF65B0A,\
		"Exit : esc .");
}

void		frac_mandelbrot(t_all *all)
{
	t_pos	pt;
	double	x1;
	double	y1;
	double	c_r;
	double	c_i;
	double	z_r;
	double	z_i;
	double	d_r;
	double	d_i;
	int		i;

	pt.x = 0;
	x1 = -2.1;
	y1 = -1.2;
	while (pt.x < WIN_SZ_X)
	{
		pt.y = 0;
		c_r = ((pt.x + all->off.x) / all->zoom) + x1;
		c_i = ((pt.y + all->off.y) / all->zoom) + y1;
		while (pt.y < WIN_SZ_Y)
		{
			c_i += 1 / all->zoom;
			z_r = c_r;
			z_i = c_i;
			d_r = z_r * z_r;
			d_i = z_i * z_i;
			i = 0;
			while ((d_r + d_i) < 4 && i < all->ite_max)
			{
				z_i = (2 * z_r * z_i) + c_i;
				z_r = d_r - d_i + c_r;
				d_r = z_r * z_r;
				d_i = z_i * z_i;
				i++;
			}
			if (i == all->ite_max)
				all->img.clrline = 0x282828;
			else
				all->img.clrline = all->colors[i & 255];
			ft_put_pxl(all, &pt);
			pt.y++;
		}
		pt.x++;
	}
}

void		frac_julia(t_all *all)
{
	t_pos	pt;
	double	x1;
	double	y1;
	double	z_r;
	double	z_i;
	double	tmp;
	int		i;

	x1 = -1.4;
	y1 = -1.2;
	pt.x = 0;
	while (pt.x < WIN_SZ_X)
	{
		pt.y = 0;
		while (pt.y < WIN_SZ_Y)
		{
			z_r = (pt.x + all->off.x) / all->zoom + x1;
			z_i = (pt.y + all->off.y) / all->zoom + y1;
			i = 0;
			while ((z_r * z_r + z_i * z_i) < 4 && i < all->ite_max)
			{
				tmp = z_r;
				z_r = (z_r * z_r) - (z_i * z_i) + all->c_r;
				z_i = (2 * tmp * z_i) + all->c_i;
				i++;
			}
			rainbow_color((double)i / (double)all->ite_max, all);
			ft_put_pxl(all, &pt);
			pt.y++;
		}
		pt.x++;
	}
}

void		exit_prog(t_all *all)
{
	free(all->env.mlx);
	free(all->env.win);
	free(all);
	exit(0);
}

int			mouse_move(int x, int y, t_all *all)
{
	if (all->f > 0)
	{
		all->c_r = (double)(x - WIN_SZ_X / 2) / all->zoom;
		all->c_i = (double)(y - WIN_SZ_Y / 2) / all->zoom;
		all->re = 1;
	}
	return (0);
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
			if (all->tab[o] == all->ite_max)
				all->img.clrline = 0x151515;
			else
				all->img.clrline = all->colors[all->tab[o] & 255];
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
			if (all->tab[o] == all->ite_max)
				all->img.clrline = 0x151515;
			else
				all->img.clrline = all->colors[all->tab[o] & 255];
			ft_put_pxl(all, &pt);
			pt.x++;
			o++;
		}
		pt.y++;
	}
	if (all->filter > 0)
		color_renorm(all, pt);
}

void		choose_frac(t_all *all)
{
	if (all->frac_no == 1)
	{
		!all->cuda_frac ? frac_mandelbrot(all) : cuda_mandelbrot(all);
		ft_strcpy(all->name, "Fractal name: Mandelbrot");
	}
	else if (all->frac_no == 2)
	{
		!all->cuda_frac ? frac_julia(all) : cuda_julia(all);
		ft_strcpy(all->name, "Fractal name: Julia");
	}
}

int			loop_hook(t_all *all)
{
	if (all->re)
	{
		if (all->re == -1)
			exit_prog(all);
		choose_frac(all);
		mlx_put_image_to_window(all->env.mlx, all->env.win, all->img.img, 0, 0);
		cartridge(all);
		all->re = 0;
	}
	return (0);
}

int			expose_hook(t_all *all)
{
	mlx_put_image_to_window(all->env.mlx, all->env.win, all->img.img, 0, 0);
	cartridge(all);
	return (0);
}

int			key_hook(int keycode, t_all *all)
{
	if (keycode == 65307)
	{
		all->re = -1;
		return (0);
	}
	else if (keycode == 'a' && all->ite_max < 20000)
		all->ite_max += 200;
	else if (keycode == 'd' && all->ite_max > 200)
		all->ite_max -= 200;
	else if (keycode == 65362)
		all->off.y += 10;
	else if (keycode == 65364)
		all->off.y -= 10;
	else if (keycode == 65361)
		all->off.x += 10;
	else if (keycode == 65363)
		all->off.x -= 10;
	else if (keycode == 49)
		all->frac_no = 1;
	else if (keycode == 50)
		all->frac_no = 2;
	else if (keycode == 'f')
		all->filter = -all->filter;
	all->re = 1;
	return (0);
}

int			mouse_hook(int button, int x, int y, t_all *all)
{
	if (button == 4)
	{
		all->zoom *= ZOOM;
		all->off.x = (all->off.x + ((WIN_SZ_X - (WIN_SZ_X / ZOOM)) / 2) +
		(x - WIN_SZ_X / 2) * (1 - (1 / ZOOM))) * ZOOM;
		all->off.y = (all->off.y + ((WIN_SZ_Y - (WIN_SZ_Y / ZOOM)) / 2) +
		(y - WIN_SZ_Y / 2) * (1 - (1 / ZOOM))) * ZOOM;
		all->re = 1;
	}
	if (button == 5)
	{
		all->zoom /= ZOOM;
		all->off.x = all->off.x / ZOOM - ((WIN_SZ_X - (WIN_SZ_X / ZOOM)) / 2) /
		ZOOM - (x - WIN_SZ_X / 2) * (1 - (1 / ZOOM)) + ZOOM;
		all->off.y = all->off.y / ZOOM - ((WIN_SZ_Y - (WIN_SZ_Y / ZOOM)) / 2) /
		ZOOM - (y - WIN_SZ_Y / 2) * (1 - (1 / ZOOM)) + ZOOM;
		all->re = 1;
	}
	if (button == 1)
	{
		all->f = -all->f;
		all->re = 1;
	}
	return (0);
}

void		all_init(t_all *all)
{
	if (!(all->env.mlx = mlx_init()))
	{
		ft_putendl_fd("You won't fuck me like that!!", 2);
		exit(2);
	}
	all->env.win = mlx_new_window(all->env.mlx, WIN_SZ_X, WIN_SZ_Y, "Fractol");
	all->img.img = mlx_new_image(all->env.mlx, WIN_SZ_X, WIN_SZ_Y);
	all->img.data = mlx_get_data_addr(all->img.img, &all->img.bpp,
	&all->img.sizeline, &all->img.endian);
	all->img.clrline = 0xF65B0A;
	all->zoom = 300;
	all->off.x = -100;
	all->off.y = -100;
	all->ite_max = 200;
	all->re = 1;
	all->f = 1;
	all->filter = -1;
	all->inc = all->img.bpp / 8;
}

void		ft_usage(void)
{
	ft_putendl_fd("fractol: illegal options\nusage: ./fractol [-cpu / -gpu]\
	[Fractal Name ...]\nfractals supported: mandelbrot, julia, newton", 2);
	exit(2);
}

void		frac_init(t_all *all, int argc, char *argv[])
{
	if (argc != 3)
		ft_usage();
	else
	{
		if (ft_strcmp(argv[1], "-cpu") == 0)
			all->cuda_frac = 0;
		else if (ft_strcmp(argv[1], "-gpu") == 0)
			all->cuda_frac = 1;
		else
			ft_usage();
		if (ft_strcmp(argv[2], "mandelbrot") == 0)
			all->frac_no = 1;
		else if (ft_strcmp(argv[2], "julia") == 0)
			all->frac_no = 2;
		else
			ft_usage();
		all_init(all);
	}
}

int			main(int argc, char *argv[])
{
	t_all		*all;
	int			i;

	all = ft_malloc(sizeof(t_all));
	i = -1;
	while (++i < 256)
		all->colors[i] = rainbow_cycle(i);
	//i = -1;
	//while (++i < 128)
	//	all->colors[128 + i] = rainbow_cycle(256 - i);
	frac_init(all, argc, argv);
	mlx_hook(all->env.win, MotionNotify, PointerMotionMask, mouse_move, all);
	mlx_key_hook(all->env.win, key_hook, all);
	mlx_mouse_hook(all->env.win, mouse_hook, all);
	mlx_loop_hook(all->env.mlx, loop_hook, all);
	mlx_expose_hook(all->env.win, expose_hook, all);
	mlx_loop(all->env.mlx);
	return (0);
}
