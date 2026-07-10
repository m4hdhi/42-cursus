/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_a.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 16:17:35 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/11 00:36:33 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line/get_next_line.h"

int	is_blank_line_strict(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (1);
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

void	strip_newline_cr(char *s)
{
	size_t	n;

	if (!s)
		return ;
	n = ft_strlen(s);
	if (n && s[n - 1] == '\n')
	{
		s[n - 1] = '\0';
		n--;
	}
	if (n && s[n - 1] == '\r')
		s[n - 1] = '\0';
}

void	strip_utf8_bom_inplace(char *s)
{
	if (!s)
		return ;
	if ((unsigned char)s[0] == 0xEF
		&& (unsigned char)s[1] == 0xBB
		&& (unsigned char)s[2] == 0xBF)
		ft_memmove(s, s + 3, ft_strlen(s + 3) + 1);
}

void	free_rows_array(char **rows, int count)
{
	int	i;

	if (!rows)
		return ;
	i = 0;
	while (i < count)
	{
		free(rows[i]);
		i++;
	}
	free(rows);
}
