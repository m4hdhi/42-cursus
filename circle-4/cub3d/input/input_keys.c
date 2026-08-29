/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 15:56:44 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/11 00:35:53 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, void *p)
{
	t_game	*g;

	g = (t_game *)p;
	if (key == KEY_W)
		g->keys.w = 1;
	if (key == KEY_A)
		g->keys.a = 1;
	if (key == KEY_S)
		g->keys.s = 1;
	if (key == KEY_D)
		g->keys.d = 1;
	if (key == KEY_LEFT)
		g->keys.left = 1;
	if (key == KEY_RIGHT)
		g->keys.right = 1;
	if (key == KEY_ESC)
		game_destroy(g, NULL, 0);
	return (0);
}

int	key_release(int key, void *p)
{
	t_game	*g;

	g = (t_game *)p;
	if (key == KEY_W)
		g->keys.w = 0;
	if (key == KEY_A)
		g->keys.a = 0;
	if (key == KEY_S)
		g->keys.s = 0;
	if (key == KEY_D)
		g->keys.d = 0;
	if (key == KEY_LEFT)
		g->keys.left = 0;
	if (key == KEY_RIGHT)
		g->keys.right = 0;
	return (0);
}
