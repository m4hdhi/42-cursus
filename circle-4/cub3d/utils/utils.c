/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 16:18:35 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/11 00:36:55 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdint.h>

void	free_split(char **s)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

int	is_space(int c)
{
	return (c == ' ' || c == '\t' || c == '\r' || c == '\v' || c == '\f');
}

int	str_ends_with(const char *s, const char *suf)
{
	size_t	a;
	size_t	b;

	if (!s || !suf)
		return (0);
	a = ft_strlen(s);
	b = ft_strlen(suf);
	if (b > a)
		return (0);
	return (!ft_strncmp(s + (a - b), suf, b));
}

int	safe_mul_size(size_t a, size_t b, size_t *out)
{
	if (a && b > SIZE_MAX / a)
		return (0);
	*out = a * b;
	return (1);
}
