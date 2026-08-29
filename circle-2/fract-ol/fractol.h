/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:16:45 by mamuzamm          #+#    #+#             */
/*   Updated: 2025/09/04 10:45:55 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx/mlx.h"
# include <math.h>
# include <unistd.h>
# include <stdlib.h>

# define SIZE 800

# define ESC 53
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124
# define R 15
# define C 8
# define P 35
# define M 46

# define SCROLL_UP 4
# define SCROLL_DOWN 5

typedef struct s_fractal
{
	void	*mlx;
	void	*window;
	void	*image;
	void	*pointer_to_image;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		x;
	int		y;
	double	zx;
	double	zy;
	double	cx;
	double	cy;
	int		color;
	double	offset_x;
	double	offset_y;
	double	zoom;
	char	*name;
	int		max_iterations;
}			t_fractal;

void		put_color_to_pixel(t_fractal *fractal, int x, int y, int colour);
int			exit_fractal(t_fractal *fractal);
void		change_iterations(t_fractal *fractal, int key_code);

void		init_fractal(t_fractal *fractal);
void		init_mlx(t_fractal *fractal);

void		calculate_mandelbrot(t_fractal *fractal);
void		calculate_julia(t_fractal *fractal);
void		calculate_burning_ship(t_fractal *fractal);

int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			draw_fractal(t_fractal *fractal, char *query);

int			key_hook(int key_code, t_fractal *fractal);
int			mouse_hook(int mouse_code, int x, int y, t_fractal *fractal);

void		draw_mandelbrot(t_fractal *fractal);
void		draw_julia(t_fractal *fractal);
void		draw_burning_ship(t_fractal *fractal);

#endif
