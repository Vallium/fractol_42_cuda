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
# include <mlx.h>
# include <X11/Xlib.h>
# include <math.h>
# include <stdlib.h>

# define WIN_SZ_X 1024
# define WIN_SZ_Y 1024
# define ZOOM 1.1

typedef unsigned char	t_byte;

typedef struct		s_color
{
	t_byte			r;
	t_byte			g;
	t_byte			b;
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

typedef struct		s_all
{
	t_env			env;
	t_img			img;
	double			zoom;
	t_pos			off;
	int				ite_max;
	int				frac_no;
	int				re;
	float			c_r;
	float			c_i;
	int				f;
}					t_all;

#endif
