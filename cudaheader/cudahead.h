#ifndef CUDA_HEAD_H
# define CUDA_HEAD_H

#include "fractol.h"
# ifdef __cplusplus
extern "C"
# endif
void	call_mandelbrot(int *i, double offx, double offy, double zoom, int ite_max, int winszx, int winszy);
void	call_julia(int *i, double offx, double offy, double zoom, int ite_max, int winszx, int winszy, double c_i, double c_r);

#endif
