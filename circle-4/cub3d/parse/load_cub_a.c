/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_cub_a.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 16:16:29 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/11 00:36:14 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line/get_next_line.h"

static int	set_player(t_game *g, int y, int x, char c)
{
	double	dir;
	double	cs;
	double	sn;

	if (g->pl.x != 0)
		return (0);
	g->pl.x = x + 0.5;
	g->pl.y = y + 0.5;
	dir = 0.0;
	if (c == 'N')
		dir = M_PI_2 * 3.0;
	else if (c == 'S')
		dir = M_PI_2;
	else if (c == 'E')
		dir = 0.0;
	else if (c == 'W')
		dir = M_PI;
	cs = cos(dir);
	sn = sin(dir);
	g->pl.dir_x = cs;
	g->pl.dir_y = sn;
	g->pl.plane_x = -sn * FOV;
	g->pl.plane_y = cs * FOV;
	return (1);
}

static int	ensure_capacity(t_game *g, t_build *b)
{
	char	**tmp;
	int		i;
	int		newcap;

	if (b->y < b->cap)
		return (1);
	newcap = 64;
	if (b->cap != 0)
		newcap = b->cap * 2;
	tmp = (char **)ft_calloc(newcap + 1, sizeof(char *));
	if (!tmp)
		return (parse_error(g, "memory allocation failed"));
	i = 0;
	while (i < b->y)
	{
		tmp[i] = b->rows[i];
		i++;
	}
	free(b->rows);
	b->rows = tmp;
	b->cap = newcap;
	return (1);
}

static int	scan_and_patch_player(t_game *g, t_build *b)
{
	int	x;

	x = 0;
	while (b->rows[b->y][x])
	{
		if (b->rows[b->y][x] == 'N'
			|| b->rows[b->y][x] == 'S'
			|| b->rows[b->y][x] == 'E'
			|| b->rows[b->y][x] == 'W')
		{
			if (!set_player(g, b->y, x, b->rows[b->y][x]))
				return (parse_error(g, "multiple player spawns"));
			b->rows[b->y][x] = '0';
			b->spawns++;
		}
		x++;
	}
	return (1);
}

int	lc_append_row_and_scan(t_game *g, t_build *b, char *ln)
{
	int	roww;

	if (!ensure_capacity(g, b))
		return (0);
	b->rows[b->y] = ft_strdup(ln);
	if (!b->rows[b->y])
		return (parse_error(g, "memory allocation failed"));
	if (!scan_and_patch_player(g, b))
		return (0);
	roww = (int)ft_strlen(b->rows[b->y]);
	if (roww > b->maxw)
		b->maxw = roww;
	b->y++;
	return (1);
}
