/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 10:37:16 by aalliot           #+#    #+#             */
/*   Updated: 2015/01/16 10:37:23 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H

# define FRACTOL_H

# include "libft.h"
# include "cudahead.h"
# include <mlx.h>
# include <X11/Xlib.h>
# include <math.h>
# include <stdlib.h>

# define WIN_SZ_X 1024
# define WIN_SZ_Y 1024
# define ZOOM 1.01
# define UINT unsigned int
# define UCHAR unsigned char

typedef struct		s_pwr
{
	float	t2;
	float	t3;
}					t_pwr;

typedef struct		s_color
{
	float			r;
	float			g;
	float			b;
}					t_color;

typedef struct		s_env
{
	void			*mlx;
	void			*win;
}					t_env;

typedef struct		s_img
{
	int				*img;
	int				bpp;
	int				sizeline;
	int				endian;
	int				clrline;
	char			*data;
}					t_img;

typedef struct		s_pos
{
	double			x;
	double			y;
}					t_pos;

typedef struct		s_rbow
{
	t_color			c;
	unsigned char	nmax;
	double			m;
	int				n;
	double			f;
	unsigned char	t;
}					t_rbow;

typedef struct		s_frac
{
	t_pos			pt;
	double			x1;
	double			y1;
	double			c_r;
	double			c_i;
	double			z_r;
	double			z_i;
	double			d_r;
	double			d_i;
	int				i;
}					t_frac;

typedef struct		s_all
{
	t_env			env;
	t_img			img;
	double			zoom;
	t_pos			off;
	int				ite_max;
	int				frac_no;
	int				re;
	double			c_r;
	double			c_i;
	int				f;
	int				filter;
	int				cuda_frac;
	char			name[50];
	UINT			colors[256];
	int				inc;
	int				color;
	int				tab[WIN_SZ_X * WIN_SZ_Y * sizeof(int)];
}					t_all;

t_color				ft_rgb_to_color(UCHAR r, UCHAR g, UCHAR b);
int					ft_color_to_int(t_color color);
t_color				ft_int_to_color(int i);
void				rainbow_color(double pos, t_all *all);

void				color_fill(int t, t_color *color, t_pwr p);
UINT				rainbow_cycle(int t);

void				ft_put_pxl(t_all *all, t_pos *pt);
void				cartridge(t_all *all);
void				color_filter(t_all *all, int *i, t_pos *pt);

void				color_renorm(t_all *all, t_pos pt);
void				color_frac(int i, t_all *all);
void				frac_calc(t_frac *frac, double c_r, double c_i, int it_max);
void				frac_mandelbrot(t_all *all);
void				frac_julia(t_all *all);
void				frac_douady(t_all *all);

void				cuda_mandelbrot(t_all *all);
void				cuda_julia(t_all *all);
void				cuda_douady(t_all *all);

void				choose_frac(t_all *all);

int					loop_hook(t_all *all);
int					expose_hook(t_all *all);
int					key_hook(int keycode, t_all *all);
int					mouse_hook(int button, int x, int y, t_all *all);

void				all_init(t_all *all);
void				ft_usage(void);
void				frac_init(t_all *all, int argc, char *argv[]);
void				exit_prog(t_all *all);
int					mouse_move(int x, int y, t_all *all);

#endif
