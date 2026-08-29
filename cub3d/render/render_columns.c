/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_columns.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 16:18:03 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/11 00:36:42 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	prepare_span_bounds(t_col *c, int *y, int *hh)
{
	*y = c->top;
	if (*y < 0)
		*y = 0;
	if (c->bot < c->top)
		c->bot = c->top;
	*hh = c->bot - c->top;
	if (*hh == 0)
		*hh = 1;
}

static int	draw_span_body(t_game *g, int x, t_col *c, double *tex_pos)
{
	int		y;
	int		hh;
	int		col;
	double	step;

	prepare_span_bounds(c, &y, &hh);
	step = (double)g->tex[c->tex_id].img.h / (double)hh;
	while (y < c->bot && y < WIN_H)
	{
		if (y >= 0)
		{
			col = sample_tex(&g->tex[c->tex_id], c->tex_x, *tex_pos);
			put_px(&g->mlx.frame, x, y, col);
		}
		*tex_pos += step;
		y++;
	}
	return (y);
}

static void	draw_textured_body(t_game *g, int x, t_col c, double tex_pos)
{
	int	y_end;

	y_end = draw_span_body(g, x, &c, &tex_pos);
	draw_floor_from(g, x, y_end);
}

void	draw_column_tex(t_game *g, int x, t_col c)
{
	double	tex_pos;
	int		y;

	y = 0;
	while (y < c.top)
	{
		put_px(&g->mlx.frame, x, y, g->cfg.ceil_rgb);
		y++;
	}
	if (c.bot < 0)
		c.bot = 0;
	if (c.top < 0)
	{
		tex_pos = (double)(-c.top);
		tex_pos = tex_pos * (double)g->tex[c.tex_id].img.h;
		tex_pos = tex_pos / (double)(c.bot - c.top);
	}
	else
		tex_pos = 0.0;
	draw_textured_body(g, x, c, tex_pos);
}
