/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_put.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 16:18:21 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/11 00:36:49 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_px(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->w || y >= img->h)
		return ;
	dst = img->addr + (y * img->line + x * (img->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

static int	texel(t_tex *t, int tx, int ty)
{
	char	*px;

	if (tx < 0)
		tx = 0;
	if (ty < 0)
		ty = 0;
	if (tx >= t->img.w)
		tx = t->img.w - 1;
	if (ty >= t->img.h)
		ty = t->img.h - 1;
	px = t->img.addr + (ty * t->img.line + tx * (t->img.bpp / 8));
	return (*(unsigned int *)px);
}

static int	blend(int a, int b, double f)
{
	int	r;
	int	g;
	int	bl;

	r = (int)(((a >> 16 & 255)) * (1.0 - f) + ((b >> 16 & 255)) * f);
	g = (int)(((a >> 8 & 255)) * (1.0 - f) + ((b >> 8 & 255)) * f);
	bl = (int)((a & 255) * (1.0 - f) + (b & 255) * f);
	return (r << 16 | g << 8 | bl);
}

int	sample_tex(t_tex *t, double tx, double ty)
{
	int		x0;
	int		y0;
	double	fx;
	double	fy;
	int		top;

	tx -= 0.5;
	ty -= 0.5;
	if (tx < 0.0)
		tx = 0.0;
	if (ty < 0.0)
		ty = 0.0;
	x0 = (int)tx;
	y0 = (int)ty;
	fx = tx - (double)x0;
	fy = ty - (double)y0;
	top = blend(texel(t, x0, y0), texel(t, x0 + 1, y0), fx);
	return (blend(top,
			blend(texel(t, x0, y0 + 1), texel(t, x0 + 1, y0 + 1), fx), fy));
}
