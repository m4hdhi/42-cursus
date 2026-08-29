/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 15:56:53 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/11 00:35:56 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rotate(t_game *g, double rt)
{
	double	odx;
	double	ody;

	odx = g->pl.dir_x;
	ody = g->pl.dir_y;
	g->pl.dir_x = odx * cos(rt) - ody * sin(rt);
	g->pl.dir_y = odx * sin(rt) + ody * cos(rt);
	odx = g->pl.plane_x;
	ody = g->pl.plane_y;
	g->pl.plane_x = odx * cos(rt) - ody * sin(rt);
	g->pl.plane_y = odx * sin(rt) + ody * cos(rt);
}

int	mouse_motion_hook(int x, int y, void *p)
{
	t_game	*g;
	int		dx;
	int		dy;

	g = (t_game *)p;
	if (!g->mouse_captured)
		return (0);
	dx = x - g->center_x;
	dy = y - g->center_y;
	g->mouse_dx += dx;
	g->mouse_dy += dy;
	if (dx != 0 || dy != 0)
		mlx_mouse_move(g->mlx.ptr, g->mlx.win, g->center_x, g->center_y);
	return (0);
}

int	mouse_move_handle(t_game *g)
{
	int	dx;
	int	dy;

	dx = g->mouse_dx;
	dy = g->mouse_dy;
	g->mouse_dx = 0;
	g->mouse_dy = 0;
	if (!g->mouse_captured || (!dx && !dy))
		return (0);
	if (dx)
		rotate(g, (double)dx * MOUSE_SENS_X);
	if (dy)
	{
		g->pl.pitch_ang -= (double)dy * MOUSE_SENS_Y_RAD;
		if (g->pl.pitch_ang > PITCH_MAX_RAD)
			g->pl.pitch_ang = PITCH_MAX_RAD;
		if (g->pl.pitch_ang < PITCH_MIN_RAD)
			g->pl.pitch_ang = PITCH_MIN_RAD;
	}
	return (0);
}

void	rotate_left_right(t_game *g)
{
	if (g->keys.left)
		rotate(g, -ROT_SPEED);
	if (g->keys.right)
		rotate(g, ROT_SPEED);
}
