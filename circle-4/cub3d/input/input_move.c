/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 15:57:00 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/11 00:35:59 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_move(t_game *g, double xx, double yy)
{
	double	nx;
	double	ny;

	nx = xx;
	ny = yy;
	if (can_move(g, nx, g->pl.y))
		g->pl.x = nx;
	if (can_move(g, g->pl.x, ny))
		g->pl.y = ny;
}

static void	move_ws(t_game *g, double ms)
{
	double	nx;
	double	ny;

	nx = g->pl.x + g->pl.dir_x * ms;
	ny = g->pl.y + g->pl.dir_y * ms;
	if (g->keys.w)
		set_move(g, nx, ny);
	nx = g->pl.x - g->pl.dir_x * ms;
	ny = g->pl.y - g->pl.dir_y * ms;
	if (g->keys.s)
		set_move(g, nx, ny);
}

static void	move_ad(t_game *g, double ms)
{
	double	nx;
	double	ny;

	nx = g->pl.x + g->pl.dir_y * ms;
	ny = g->pl.y - g->pl.dir_x * ms;
	if (g->keys.a)
		set_move(g, nx, ny);
	nx = g->pl.x - g->pl.dir_y * ms;
	ny = g->pl.y + g->pl.dir_x * ms;
	if (g->keys.d)
		set_move(g, nx, ny);
}

void	handle_move(t_game *g)
{
	double	ms;

	ms = MOVE_SPEED;
	move_ws(g, ms);
	move_ad(g, ms);
}
