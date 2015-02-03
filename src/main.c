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
		"Change color rainbow : c .");
	mlx_string_put(all->env.mlx, all->env.win, 10, 150, 0xF65B0A,\
		"Zoom : Scroll Mouse .");
	mlx_string_put(all->env.mlx, all->env.win, 10, 170, 0xF65B0A,\
		"Exit : esc .");
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
	else if (all->frac_no == 3)
	{
		!all->cuda_frac ? frac_douady(all) : cuda_douady(all);
		ft_strcpy(all->name, "Fractal name: Douady Rabbit");
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
	if (keycode == 'a' && all->ite_max < 20000)
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
	else if (keycode == 51)
		all->frac_no = 3;
	else if (keycode == 'f')
		all->filter = -all->filter;
	else if (keycode == 'c')
		all->color = -all->color;
	all->re = keycode == 65307 ? -1 : 1;
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
	all->color = 1;
	all->inc = all->img.bpp / 8;
}

void		ft_usage(void)
{
	ft_putendl_fd("fractol: illegal options\nusage: ./fractol [-cpu / -gpu]\
	[Fractal Name ...]\nfractals supported: mandelbrot, julia, douady", 2);
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
		else if (ft_strcmp(argv[2], "douady") == 0)
			all->frac_no = 3;
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
	while (++i < 128)
		all->colors[i] = rainbow_cycle(i);
	i = -1;
	while (++i < 128)
		all->colors[128 + i] = rainbow_cycle(256 - i);
	frac_init(all, argc, argv);
	mlx_hook(all->env.win, MotionNotify, PointerMotionMask, mouse_move, all);
	mlx_key_hook(all->env.win, key_hook, all);
	mlx_mouse_hook(all->env.win, mouse_hook, all);
	mlx_loop_hook(all->env.mlx, loop_hook, all);
	mlx_expose_hook(all->env.win, expose_hook, all);
	mlx_loop(all->env.mlx);
	return (0);
}
