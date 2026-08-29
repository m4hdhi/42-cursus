/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 15:56:12 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/11 00:35:39 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_tex(t_mlx *m, t_tex *t, char *path)
{
	t->img.ptr = mlx_xpm_file_to_image(m->ptr, path, &t->img.w, &t->img.h);
	if (!t->img.ptr)
		return (0);
	t->img.addr = mlx_get_data_addr(t->img.ptr, &t->img.bpp, &t->img.line,
			&t->img.endian);
	return (1);
}

static int	load_all_textures(t_game *g)
{
	if (!load_tex(&g->mlx, &g->tex[0], g->cfg.no_path))
		return (write(2, "Error\ntexture NO: ", 19),
			write(2, g->cfg.no_path, ft_strlen(g->cfg.no_path)),
			write(2, "\n", 1), 0);
	if (!load_tex(&g->mlx, &g->tex[1], g->cfg.so_path))
		return (write(2, "Error\ntexture SO: ", 19),
			write(2, g->cfg.so_path, ft_strlen(g->cfg.so_path)),
			write(2, "\n", 1), 0);
	if (!load_tex(&g->mlx, &g->tex[2], g->cfg.we_path))
		return (write(2, "Error\ntexture WE: ", 19),
			write(2, g->cfg.we_path, ft_strlen(g->cfg.we_path)),
			write(2, "\n", 1), 0);
	if (!load_tex(&g->mlx, &g->tex[3], g->cfg.ea_path))
		return (write(2, "Error\n'texture EA: ", 20),
			write(2, g->cfg.ea_path, ft_strlen(g->cfg.ea_path)),
			write(2, "\n", 1), 0);
	return (1);
}

int	game_init(t_game *g)
{
	g->mlx.ptr = mlx_init();
	if (!g->mlx.ptr)
		return (write(2, "Error\nmlx_init failed\n", 22), 0);
	g->mlx.win = mlx_new_window(g->mlx.ptr, WIN_W, WIN_H, "cub3d");
	if (!g->mlx.win)
		return (write(2, "Error\nmlx_new_window failed\n", 28),
			game_destroy(g, NULL, 1), 0);
	g->mlx.frame.ptr = mlx_new_image(g->mlx.ptr, WIN_W, WIN_H);
	if (!g->mlx.frame.ptr)
		return (write(2, "Error\nmlx_new_image failed\n", 27),
			game_destroy(g, NULL, 1), 0);
	g->mlx.frame.addr = mlx_get_data_addr(g->mlx.frame.ptr, &g->mlx.frame.bpp,
			&g->mlx.frame.line, &g->mlx.frame.endian);
	g->mlx.frame.w = WIN_W;
	g->mlx.frame.h = WIN_H;
	if (!load_all_textures(g))
		return (game_destroy(g, NULL, 1), 0);
	g->keys = (t_keys){0, 0, 0, 0, 0, 0};
	g->mouse_captured = 0;
	g->center_x = WIN_W / 2;
	g->center_y = WIN_H / 2;
	g->pl.pitch_ang = 0.0;
	return (1);
}
