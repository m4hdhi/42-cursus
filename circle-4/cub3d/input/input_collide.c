/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_collide.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 15:57:08 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/11 00:35:51 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	cell_free(t_game *g, double nx, double ny)
{
	int	ix;
	int	iy;
	int	rowlen;

	ix = (int)nx;
	iy = (int)ny;
	if (iy < 0 || iy >= g->map.h)
		return (0);
	if (ix < 0)
		return (0);
	rowlen = (int)ft_strlen(g->map.grid[iy]);
	if (ix >= rowlen)
		return (1);
	return (g->map.grid[iy][ix] != '1');
}

int	can_move(t_game *g, double nx, double ny)
{
	if (!cell_free(g, nx - COLL_PAD, ny - COLL_PAD))
		return (0);
	if (!cell_free(g, nx + COLL_PAD, ny - COLL_PAD))
		return (0);
	if (!cell_free(g, nx - COLL_PAD, ny + COLL_PAD))
		return (0);
	if (!cell_free(g, nx + COLL_PAD, ny + COLL_PAD))
		return (0);
	return (1);
}
