/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cfg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 16:17:30 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/11 00:36:31 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	handle_path(char **dst, int *flag, char *line, const char *id)
{
	char	*tmp;
	int		r;

	tmp = NULL;
	r = parse_id_path(&tmp, line, id);
	if (r == -1)
		return (-1);
	if (r == 1)
	{
		if (*flag)
		{
			free(tmp);
			return (-2);
		}
		*dst = tmp;
		*flag = 1;
		return (1);
	}
	return (0);
}

static int	handle_color(int *dst, int *flag, char *line, const char *id)
{
	int	r;

	r = parse_color_csv(dst, line, id);
	if (r == -1)
		return (-1);
	if (r == 1)
	{
		if (*flag)
			return (-2);
		*flag = 1;
		return (1);
	}
	return (0);
}

static int	try_paths(t_game *g, char *line, t_parsef *f)
{
	int	r;

	r = handle_path(&g->cfg.no_path, &f->no, line, "NO ");
	if (r != 0)
		return (r);
	r = handle_path(&g->cfg.so_path, &f->so, line, "SO ");
	if (r != 0)
		return (r);
	r = handle_path(&g->cfg.we_path, &f->we, line, "WE ");
	if (r != 0)
		return (r);
	return (handle_path(&g->cfg.ea_path, &f->ea, line, "EA "));
}

static int	try_colors(t_game *g, char *line, t_parsef *f)
{
	int	r;

	r = handle_color(&g->cfg.floor_rgb, &f->f, line, "F ");
	if (r != 0)
		return (r);
	return (handle_color(&g->cfg.ceil_rgb, &f->c, line, "C "));
}

int	parse_cfg_line(t_game *g, char *line, t_parsef *f)
{
	int	r;

	r = try_paths(g, line, f);
	if (r != 0)
	{
		if (r > 0)
			return (1);
		return (r);
	}
	r = try_colors(g, line, f);
	if (r != 0)
	{
		if (r > 0)
			return (1);
		return (r);
	}
	return (0);
}
