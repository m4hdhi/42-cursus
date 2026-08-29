/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:23:58 by mamuzamm          #+#    #+#             */
/*   Updated: 2025/01/10 17:04:59 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_wordlen(const char *s, char c)
{
	size_t	ret;

	ret = 0;
	while (*s)
	{
		if (*s != c)
		{
			++ret;
			while (*s && *s != c)
				++s;
		}
		else
			++s;
	}
	return (ret);
}

char	**free_mem(char **mem, size_t m)
{
	size_t	i;

	i = 0;
	while (i < m)
	{
		free(mem[i]);
		i++;
	}
	free(mem);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	char	**ret;
	size_t	i;
	size_t	len;

	if (!s)
		return (0);
	i = 0;
	ret = malloc(sizeof(char *) * (ft_wordlen(s, c) + 1));
	if (!ret)
		return (0);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			break ;
		len = 0;
		while (*s && *s != c && ++len)
			++s;
		ret[i] = ft_substr(s - len, 0, len);
		if (!ret[i++])
			return (free_mem(ret, i));
	}
	ret[i] = 0;
	return (ret);
}
