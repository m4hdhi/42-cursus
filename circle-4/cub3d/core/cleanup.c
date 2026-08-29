/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 15:55:56 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/11 00:35:25 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_cfg(t_cfg *c)
{
	free(c->no_path);
	free(c->so_path);
	free(c->we_path);
	free(c->ea_path);
}

void	game_destroy(t_game *g, const char *msg, int ec)
{
	int	i;

	if (msg)
		write(2, msg, ft_strlen(msg));
	if (g->mlx.ptr && g->mlx.frame.ptr)
		mlx_destroy_image(g->mlx.ptr, g->mlx.frame.ptr);
	i = 0;
	while (i < 4)
	{
		if (g->tex[i].img.ptr)
			mlx_destroy_image(g->mlx.ptr, g->tex[i].img.ptr);
		i++;
	}
	if (g->mlx.ptr && g->mlx.win)
		mlx_destroy_window(g->mlx.ptr, g->mlx.win);
	if (g->mlx.ptr)
	{
		mlx_destroy_display(g->mlx.ptr);
		free(g->mlx.ptr);
	}
	free_cfg(&g->cfg);
	free_split(g->map.grid);
	exit(ec);
}
