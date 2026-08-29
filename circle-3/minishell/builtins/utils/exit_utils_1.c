/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 04:03:48 by mosami            #+#    #+#             */
/*   Updated: 2026/01/29 04:17:01 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	exit_error(char **str, t_shl *shl)
{
	write(2, "minishell: exit: ", 17);
	write(2, str[1], ft_strlen(str[1]));
	write(2, ": numeric argument required\n", 28);
	free_array(shl->env);
	free_array(str);
	cleanup_shell(shl, TNT);
	exit(2);
}

static int	check_digit_sequence(char *s, int *i, int *len)
{
	while (s[*i])
	{
		if (s[*i] >= '0' && s[*i] <= '9')
		{
			(*i)++;
			(*len)++;
		}
		else
			return (0);
	}
	return (1);
}

void	valid_num(char *s, char **str, t_shl *shl)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!check_digit_sequence(s, &i, &len))
		exit_error(str, shl);
	if (len >= 20)
		exit_error(str, shl);
}
