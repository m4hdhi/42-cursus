/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_columns_fill.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 16:17:56 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/11 00:36:40 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	clamp_mid(int mid)
{
	if (mid < 0)
		return (0);
	if (mid > WIN_H)
		return (WIN_H);
	return (mid);
}

void	draw_ceiling_until(t_game *g, int x, int endy)
{
	int	y;

	y = 0;
	while (y < endy)
	{
		put_px(&g->mlx.frame, x, y, g->cfg.ceil_rgb);
		y++;
	}
}

void	draw_floor_from(t_game *g, int x, int starty)
{
	int	y;

	y = starty;
	while (y < WIN_H)
	{
		put_px(&g->mlx.frame, x, y, g->cfg.floor_rgb);
		y++;
	}
}

void	draw_column_flat(t_game *g, int x, int pitchi)
{
	int	mid;

	mid = WIN_H / 2 + pitchi;
	mid = clamp_mid(mid);
	draw_ceiling_until(g, x, mid);
	draw_floor_from(g, x, mid);
}

void	draw_column_flat_wrap(t_game *g, int x, int pitchi)
{
	draw_column_flat(g, x, pitchi);
}
