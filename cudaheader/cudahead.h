/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cudahead.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 16:08:27 by aalliot           #+#    #+#             */
/*   Updated: 2015/02/03 16:08:30 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUDA_HEAD_H
# define CUDA_HEAD_H

#include "fractol.h"

# ifdef __cplusplus
extern "C"
# endif

void	call_mandelbrot(int *tab, double offx, double offy, double zoom, int ite_max, int winszx, int winszy);
void	call_julia(int *tab, double offx, double offy, double zoom, int ite_max, int winszx, int winszy, double c_i, double c_r);
void	call_douady(int *tab, double offx, double offy, double zoom, int ite_max, int winszx, int winszy);

#endif
