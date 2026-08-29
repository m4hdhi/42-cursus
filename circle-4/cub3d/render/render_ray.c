/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 16:18:27 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/11 00:36:51 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	step_dda(t_dda *st, t_rdir d)
{
	if (st->sdx < st->sdy)
	{
		st->sdx += st->ddx;
		if (d.x < 0.0)
			st->mx -= 1;
		else
			st->mx += 1;
		st->side = 0;
	}
	else
	{
		st->sdy += st->ddy;
		if (d.y < 0.0)
			st->my -= 1;
		else
			st->my += 1;
		st->side = 1;
	}
	return (1);
}

static double	compute_wd(t_game *g, t_rdir d, t_dda *st)
{
	double	wd;

	if (st->side == 0)
	{
		if (d.x < 0.0)
			wd = (st->mx + 1 - g->pl.x) / d.x;
		else
			wd = (st->mx - g->pl.x) / d.x;
	}
	else
	{
		if (d.y < 0.0)
			wd = (st->my + 1 - g->pl.y) / d.y;
		else
			wd = (st->my - g->pl.y) / d.y;
	}
	return (wd);
}

static void	set_ori_and_wx(t_game *g, t_rdir d, t_dda *st, t_rayhit *hit)
{
	double	wd;
	double	wx;

	wd = compute_wd(g, d, st);
	if (st->side == 0)
	{
		if (d.x > 0.0)
			hit->ori = 3;
		else
			hit->ori = 2;
		wx = g->pl.y + wd * d.y;
	}
	else
	{
		if (d.y > 0.0)
			hit->ori = 1;
		else
			hit->ori = 0;
		wx = g->pl.x + wd * d.x;
	}
	wx -= floor(wx);
	hit->walld = wd;
	hit->wx = wx;
}

static int	dda_walk(t_game *g, t_rdir d, t_dda *st)
{
	int	hit;

	st->mx = (int)g->pl.x;
	st->my = (int)g->pl.y;
	hit = 0;
	while (!hit)
	{
		step_dda(st, d);
		if (st->my < 0 || st->my >= g->map.h)
			return (0);
		if (st->mx < 0 || st->mx >= (int)ft_strlen(g->map.grid[st->my]))
			return (0);
		hit = (g->map.grid[st->my][st->mx] == '1');
	}
	return (1);
}

int	raycast_cell(t_game *g, double rdx, double rdy, t_rayhit *hit)
{
	t_dda	st;
	t_rdir	d;
	double	wd;

	d.x = rdx;
	d.y = rdy;
	init_dda(g, d, &st);
	if (!dda_walk(g, d, &st))
		return (0);
	wd = compute_wd(g, d, &st);
	if (wd <= 0.0)
	{
		hit->walld = 0.0;
		hit->ori = 0;
		hit->wx = 0.0;
		return (0);
	}
	set_ori_and_wx(g, d, &st, hit);
	if (hit->walld <= 0.0)
		return (0);
	return (1);
}
