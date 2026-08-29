/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 15:56:04 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/11 00:35:37 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	on_close(void *p)
{
	game_destroy((t_game *)p, NULL, 0);
	return (0);
}

int	expose_redraw(void *p)
{
	(void)p;
	return (0);
}

int	game_loop(void *param)
{
	t_game	*g;

	g = (t_game *)param;
	handle_move(g);
	rotate_left_right(g);
	mouse_move_handle(g);
	draw_frame(g);
	mlx_put_image_to_window(g->mlx.ptr, g->mlx.win, g->mlx.frame.ptr, 0, 0);
	return (0);
}
