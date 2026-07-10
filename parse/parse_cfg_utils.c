/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cfg_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 16:17:23 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/11 00:36:29 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_csv_tokens(char **p)
{
	int	i;

	if (!p || !p[0] || !p[1] || !p[2] || p[3])
		return (0);
	i = 0;
	while (p[i])
	{
		if (ft_strlen(p[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

static int	clamp_rgb_and_pack(int r, int g, int b, int *rgb)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
	*rgb = (r << 16) | (g << 8) | b;
	return (1);
}

static int	parse_uint_strict(const char *s, int *out)
{
	size_t	i;
	long	v;

	i = 0;
	while (s[i] && is_space((unsigned char)s[i]))
		i++;
	if (!ft_isdigit((unsigned char)s[i]))
		return (0);
	v = 0;
	while (ft_isdigit((unsigned char)s[i]))
	{
		v = v * 10 + (s[i] - '0');
		if (v > 2147483647)
			return (0);
		i++;
	}
	while (s[i] && is_space((unsigned char)s[i]))
		i++;
	if (s[i] != '\0')
		return (0);
	*out = (int)v;
	return (1);
}

int	color_from_csv(const char *s, int *rgb)
{
	char	**p;
	int		r;
	int		g;
	int		b;

	p = ft_split(s, ',');
	if (!check_csv_tokens(p))
		return (free_split(p), 0);
	if (!parse_uint_strict(p[0], &r)
		|| !parse_uint_strict(p[1], &g)
		|| !parse_uint_strict(p[2], &b))
		return (free_split(p), 0);
	if (!clamp_rgb_and_pack(r, g, b, rgb))
		return (free_split(p), 0);
	free_split(p);
	return (1);
}

int	parse_color_csv(int *dst, char *line, const char *id)
{
	int	i;

	if (ft_strncmp(line, id, (int)ft_strlen(id)) != 0)
		return (0);
	i = (int)ft_strlen(id);
	while (line[i] && is_space((unsigned char)line[i]))
		i++;
	if (color_from_csv(line + i, dst))
		return (1);
	return (-1);
}
