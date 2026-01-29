/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 04:05:05 by mosami            #+#    #+#             */
/*   Updated: 2026/01/29 04:17:37 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_msg(char **str, t_shl *shl)
{
	write(2, "exit\n", 5);
	write(2, "minishell: exit: ", 17);
	write(2, str[1], ft_strlen(str[1]));
	write(2, ": numeric argument required\n", 28);
	free_array(shl->env);
	free_array(str);
	cleanup_shell(shl, TNT);
	exit(255);
}

void	neg_num_exit(unsigned long long exit_num, t_shl *shl, char **str)
{
	long	negative_num;

	negative_num = -exit_num;
	negative_num = negative_num % 256;
	free_array(shl->env);
	free_array(str);
	cleanup_shell(shl, TNT);
	write(1, "exit\n", 5);
	exit(negative_num);
}

unsigned long long	symbol_check(char *str, int *check)
{
	unsigned long long	exit_num;

	if (str[0] == '-')
	{
		exit_num = ft_atol(str + 1);
		*check = 0;
	}
	else
		exit_num = ft_atol(str);
	return (exit_num);
}

void	num_valid_check(unsigned long long e, int c, char **str,
		t_shl *shl)
{
	if (e > LONG_MAX && c == 1)
		error_msg(str, shl);
	else if (e > (ULONG_MAX - LONG_MIN) + 1 && c == 0)
		error_msg(str, shl);
}

void	exit_cmd(char **str, t_shl *shl)
{
	unsigned long long	exit_num;
	int					check;

	check = 1;
	if (!ft_strncmp(str[0], "exit", 4) && str[1] != NULL && str[2] != NULL)
	{
		(write(2, "exit\n", 6), write(2, "exit: too many arguments\n", 26));
		shl->e_stat = 1;
		return ;
	}
	else if (!ft_strncmp(str[0], "exit", 5) && str[1] != NULL)
	{
		valid_num(str[1], str, shl);
		exit_num = symbol_check(str[1], &check);
		num_valid_check(exit_num, check, str, shl);
		if (!check)
			neg_num_exit(exit_num, shl, str);
		if (exit_num >= 256 && check == 1)
			exit_num = exit_num % 256;
		(free_array(str), free_array(shl->env), cleanup_shell(shl, TNT),
			write(2, "exit\n", 6), exit(exit_num));
	}
	else if (!ft_strncmp(str[0], "exit", 5) && str[1] == NULL)
		(free_array(str), free_array(shl->env), cleanup_shell(shl, TNT),
			write(2, "exit\n", 5), exit(0));
}
