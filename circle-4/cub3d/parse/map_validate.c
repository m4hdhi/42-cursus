/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 16:17:10 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/11 00:36:27 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	fill_spaces(char **p, t_rect *r)
{
	r->y = 0;
	while (r->y < (int)r->rows)
	{
		p[r->y] = (char *)ft_calloc(r->cols + 1, 1);
		if (!p[r->y])
			return (0);
		r->x = 0;
		while (r->x < (int)r->cols)
		{
			p[r->y][r->x] = ' ';
			r->x++;
		}
		r->y++;
	}
	return (1);
}

static void	copy_into_pad(t_map *m, char **p, t_rect *r)
{
	r->y = 0;
	while (r->y < r->h)
	{
		r->x = 0;
		while (r->x < (int)ft_strlen(m->grid[r->y]) && r->x < r->w)
		{
			p[r->y + 1][r->x + 1] = m->grid[r->y][r->x];
			r->x++;
		}
		r->y++;
	}
}

static char	**pad_map_rect(t_map *m, int *pw, int *ph)
{
	char	**p;
	t_rect	r;
	size_t	cells;
	size_t	bytes;

	r.w = m->w;
	r.h = m->h;
	if (!(r.w > 0 && r.h > 0))
		return (NULL);
	*pw = r.w + 2;
	*ph = r.h + 2;
	r.rows = (size_t)r.h + 2;
	r.cols = (size_t)r.w + 2;
	if (!safe_mul_size(r.rows, r.cols, &cells))
		return (NULL);
	if (!safe_mul_size(cells, sizeof(char), &bytes))
		return (NULL);
	p = (char **)ft_calloc(r.rows + 1, sizeof(char *));
	if (!p)
		return (NULL);
	if (!fill_spaces(p, &r))
		return (free_split(p), (char **) NULL);
	copy_into_pad(m, p, &r);
	return (p);
}

static int	check_row_chars(char *row)
{
	int	i;

	i = 0;
	while (row[i])
	{
		if (!(row[i] == '0' || row[i] == '1' || row[i] == ' '))
			return (0);
		i++;
	}
	return (1);
}

int	validate_map(t_map *m)
{
	int		y;
	int		pw;
	int		ph;
	int		rc;
	char	**pad;

	y = 0;
	while (y < m->h)
	{
		if (!check_row_chars(m->grid[y]))
			return (write(2, "Error\ninvalid map char\n", 23), 0);
		y++;
	}
	pad = pad_map_rect(m, &pw, &ph);
	if (!pad)
		return (write(2, "Error\nmap too large or malloc failed\n", 36), 0);
	rc = flood_touch_floor(pad, pw, ph);
	free_split(pad);
	if (rc < 0)
		return (write(2, "Error\nmap too large or malloc failed\n", 36), 0);
	if (rc > 0)
		return (write(2, "Error\nmap not closed\n", 21), 0);
	return (1);
}
