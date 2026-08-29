/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 16:18:15 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/11 00:36:47 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_col(t_game *g, t_rayhit *h, t_col *c)
{
	c->tex_id = h->ori;
	c->tex_x = h->wx * (double)g->tex[c->tex_id].img.w;
	if (h->ori == 1 || h->ori == 2)
		c->tex_x = (double)g->tex[c->tex_id].img.w - c->tex_x;
}

static void	draw_x(t_game *g, int x, int pitchi)
{
	double		cam;
	t_rdir		d;
	t_rayhit	h;
	int			hh;
	t_col		c;

	cam = 2.0 * (double)x / (double)WIN_W - 1.0;
	d.x = g->pl.dir_x + g->pl.plane_x * cam;
	d.y = g->pl.dir_y + g->pl.plane_y * cam;
	if (!raycast_cell(g, d.x, d.y, &h))
	{
		draw_column_flat_wrap(g, x, pitchi);
		return ;
	}
	hh = (int)((double)WIN_H / h.walld);
	c.top = -hh / 2 + WIN_H / 2 + pitchi;
	c.bot = hh / 2 + WIN_H / 2 + pitchi;
	setup_col(g, &h, &c);
	draw_column_tex(g, x, c);
}

void	draw_frame(t_game *g)
{
	int		x;
	double	shift;
	int		pitchi;

	shift = tan(g->pl.pitch_ang) * (WIN_H / 2.0);
	if (shift > 100000.0)
		shift = 100000.0;
	if (shift < -100000.0)
		shift = -100000.0;
	pitchi = (int)shift;
	x = 0;
	while (x < WIN_W)
	{
		draw_x(g, x, pitchi);
		x++;
	}
}
