/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splits_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 07:52:08 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/01/29 04:19:37 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*extract_cmd_from_redir(char *first_half, char *str, int start,
		int append)
{
	char	*cmd_flags;

	if (!first_half)
		(free(str), print_exit(ERR_MALLOC));
	cmd_flags = exp_after_redir_node(str, first_half, start + 1 + append);
	if (!cmd_flags)
		(free(first_half), free(str), print_exit(ERR_MALLOC));
	free(first_half);
	if (ft_strlen(cmd_flags) == 0)
		return (free(cmd_flags), NULL);
	return (cmd_flags);
}

int	skip_qoutes(char *str, int *i)
{
	if (str[*i] == '"' || str[*i] == '\'')
	{
		*i = inside_qoutes(str[*i], str, *i);
		return (TRUE);
	}
	return (FALSE);
}

int	break_skip_spaces(char *str, int *i)
{
	if (skip_spaces(str, i))
	{
		if (str[*i] == '\0')
			return (TRUE);
		*i = *i - 1;
	}
	return (FALSE);
}

void	create_args_array(char *str, char ***args)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = -1;
	while (i <= ft_strlen(str))
	{
		if (skip_qoutes(str, &i))
			continue ;
		else
		{
			if (str[i] == ' ' || str[i] == '\0')
			{
				(*args)[++k] = (ft_substr(str, j, i - j));
				if (break_skip_spaces(str, &i))
					break ;
				j = i + 1;
			}
		}
		i++;
	}
	(*args)[++k] = NULL;
}

int	count_args(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (++i <= ft_strlen(str))
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			i = inside_qoutes(str[i], str, i);
			if (i-- == -1)
				break ;
			continue ;
		}
		else
		{
			if (str[i] == ' ' || str[i] == '\0')
				count++;
			if (skip_spaces(str, &i))
				if (str[i--] == '\0')
					break ;
		}
	}
	return (count);
}
