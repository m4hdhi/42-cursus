/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 07:52:26 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/01/29 04:19:45 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirection_ahead(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			i = inside_qoutes(str[i], str, i);
			continue ;
		}
		if (str[i] == '<' || str[i] == '>')
			return (1);
		i++;
	}
	return (0);
}

int	spl_operator_ahead(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			i = inside_qoutes(str[i], str, i);
			continue ;
		}
		if ((str[i] == '&' && str[i + 1] == '&') || (str[i] == '|' && str[i
					+ 1] == '|'))
			return (1);
		i++;
	}
	return (0);
}

int	operator_ahead(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			i = inside_qoutes(str[i], str, i);
			continue ;
		}
		if (str[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

int	skip_spaces(char *str, int *i)
{
	int	flag;

	flag = 0;
	while (str[*i] == ' ')
	{
		flag = 1;
		*i += 1;
	}
	return (flag);
}
