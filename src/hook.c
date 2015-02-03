/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 20:10:27 by aalliot           #+#    #+#             */
/*   Updated: 2015/02/03 20:10:29 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
