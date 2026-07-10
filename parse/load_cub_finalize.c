/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_cub_finalize.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 16:16:49 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/11 00:36:23 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	alloc_grid_from_build(t_game *g, t_build *b)
{
	g->map.h = b->y;
	g->map.w = b->maxw;
	g->map.grid = (char **)ft_calloc(g->map.h + 1, sizeof(char *));
	if (!g->map.grid)
	{
		free_rows_array(b->rows, b->y);
		write(2, "Error\nmemory allocation failed\n", 31);
		return (0);
	}
	return (1);
}

static void	move_rows_to_map(t_game *g, t_build *b)
{
	int	i;

	i = 0;
	while (i < g->map.h)
	{
		g->map.grid[i] = b->rows[i];
		b->rows[i] = NULL;
		i++;
	}
	free(b->rows);
}

static int	validate_or_cleanup(t_game *g)
{
	if (!validate_map(&g->map))
	{
		free_split(g->map.grid);
		g->map.grid = NULL;
		g->map.w = 0;
		g->map.h = 0;
		free_cfg_fields(&g->cfg);
		return (0);
	}
	return (1);
}

int	lc_finalize_map(t_game *g, t_build *b)
{
	if (!alloc_grid_from_build(g, b))
		return (0);
	move_rows_to_map(g, b);
	return (validate_or_cleanup(g));
}
