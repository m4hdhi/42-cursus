/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:16:45 by mamuzamm          #+#    #+#             */
/*   Updated: 2025/09/02 13:41:55 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_fractal(t_fractal *fractal)
{
	fractal->x = 0;
	fractal->y = 0;
	fractal->cx = 0.0;
	fractal->cy = 0.0;
	fractal->color = 0x04e5fc;
	fractal->zoom = 300;
	fractal->offset_x = -1.33;
	fractal->offset_y = -1.33;
	fractal->max_iterations = 42;
}

void	init_mlx(t_fractal *fractal)
{
	fractal->mlx = mlx_init();
	fractal->window = mlx_new_window(fractal->mlx, SIZE, SIZE, "Fract-ol");
	fractal->image = mlx_new_image(fractal->mlx, SIZE, SIZE);
	fractal->pointer_to_image = mlx_get_data_addr(fractal->image,
			&fractal->bits_per_pixel,
			&fractal->size_line,
			&fractal->endian);
}

static void	set_julia_from_cli(t_fractal *f, int argc, char **argv)
{
	if (argc == 4 && ft_strncmp(argv[1], "julia", 5) == 0)
	{
		f->cx = atof(argv[2]);
		f->cy = atof(argv[3]);
	}
}

int	draw_fractal(t_fractal *fractal, char *query)
{
	if (ft_strncmp(query, "mandel", 7) == 0)
		draw_mandelbrot(fractal);
	else if (ft_strncmp(query, "julia", 6) == 0)
	{
		if (!fractal->cx && !fractal->cy)
		{
			fractal->cx = -0.745429;
			fractal->cy = 0.05;
		}
		draw_julia(fractal);
	}
	else if (ft_strncmp(query, "ship", 5) == 0)
		draw_burning_ship(fractal);
	else
	{
		write(1, "Available fractals: mandel, julia, ship\n", 40);
		exit_fractal(fractal);
	}
	mlx_put_image_to_window(fractal->mlx, fractal->window, fractal->image, 0,
		0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_fractal	*fractal;

	if (!((argc == 2) || (argc == 4 && ft_strncmp(argv[1], "julia", 5) == 0)))
	{
		write(1, "Usage:\n", 7);
		write(1, "  ./fractol mandel\n", 19);
		write(1, "  ./fractol julia [cx cy]\n", 26);
		write(1, "  ./fractol ship\n", 18);
		return (0);
	}
	fractal = malloc(sizeof(t_fractal));
	init_fractal(fractal);
	set_julia_from_cli(fractal, argc, argv);
	init_mlx(fractal);
	mlx_key_hook(fractal->window, key_hook, fractal);
	mlx_mouse_hook(fractal->window, mouse_hook, fractal);
	mlx_hook(fractal->window, 17, 0L, exit_fractal, fractal);
	draw_fractal(fractal, argv[1]);
	mlx_loop(fractal->mlx);
	return (0);
}
