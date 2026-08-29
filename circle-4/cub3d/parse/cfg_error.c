/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cfg_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 16:16:20 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/11 00:36:12 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_cfg_fields(t_cfg *c)
{
	if (!c)
		return ;
	free(c->no_path);
	c->no_path = NULL;
	free(c->so_path);
	c->so_path = NULL;
	free(c->we_path);
	c->we_path = NULL;
	free(c->ea_path);
	c->ea_path = NULL;
}

int	parse_error_rows(char **rows, int y, const char *msg)
{
	if (rows)
		free_rows_array(rows, y);
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (0);
}

int	parse_error(t_game *g, const char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	free_cfg_fields(&g->cfg);
	if (g->map.grid)
	{
		free_split(g->map.grid);
		g->map.grid = NULL;
	}
	g->map.w = 0;
	g->map.h = 0;
	return (0);
}
