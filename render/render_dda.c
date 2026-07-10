/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_dda.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 16:18:08 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/11 00:36:45 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_dda_x(t_game *g, t_rdir d, t_dda *st, int map_x)
{
	if (d.x == 0.0)
		st->ddx = 1e30;
	else
		st->ddx = fabs(1.0 / d.x);
	if (d.x < 0.0)
	{
		st->sdx = (g->pl.x - map_x) * st->ddx;
		st->mx = map_x - 1;
	}
	else
	{
		st->sdx = (map_x + 1.0 - g->pl.x) * st->ddx;
		st->mx = map_x + 1;
	}
}

static void	init_dda_y(t_game *g, t_rdir d, t_dda *st, int map_y)
{
	if (d.y == 0.0)
		st->ddy = 1e30;
	else
		st->ddy = fabs(1.0 / d.y);
	if (d.y < 0.0)
	{
		st->sdy = (g->pl.y - map_y) * st->ddy;
		st->my = map_y - 1;
	}
	else
	{
		st->sdy = (map_y + 1.0 - g->pl.y) * st->ddy;
		st->my = map_y + 1;
	}
}

void	init_dda(t_game *g, t_rdir d, t_dda *st)
{
	int	map_x;
	int	map_y;

	map_x = (int)g->pl.x;
	map_y = (int)g->pl.y;
	init_dda_x(g, d, st, map_x);
	init_dda_y(g, d, st, map_y);
}
