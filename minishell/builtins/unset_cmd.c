/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 04:05:21 by mosami            #+#    #+#             */
/*   Updated: 2026/01/29 04:17:45 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_node_exp(t_path **paths, int pos)
{
	t_exp	*tmp_exp;
	t_exp	*prev_exp;
	int		i;

	i = 0;
	tmp_exp = (*paths)->exp_struct;
	while (tmp_exp)
	{
		if (i == pos)
			break ;
		i++;
		prev_exp = tmp_exp;
		tmp_exp = tmp_exp->next;
	}
	if (tmp_exp == NULL)
		return ;
	if (prev_exp != NULL)
	{
		if (!check_prev_exp(i, paths, prev_exp, tmp_exp))
			return ;
	}
	else
		(*paths)->exp_struct = tmp_exp->next;
	free(tmp_exp->exp);
	free(tmp_exp);
}

void	remove_node_env(t_path **paths, int pos)
{
	t_env	*tmp_env;
	t_env	*prev_env;
	int		i;

	i = 0;
	tmp_env = (*paths)->env_struct;
	while (tmp_env)
	{
		if (i == pos)
			break ;
		i++;
		prev_env = tmp_env;
		tmp_env = tmp_env->next;
	}
	if (tmp_env == NULL)
		return ;
	if (prev_env != NULL)
	{
		if (!check_prev_env(i, paths, prev_env, tmp_env))
			return ;
	}
	else
		(*paths)->env_struct = tmp_env->next;
	free(tmp_env->env);
	free(tmp_env);
}

void	unset_exp_list(t_path **paths, char *str, int *i, int *exit_stat)
{
	t_exp	*tmp;
	int		pos;
	int		f;

	if (!valid_unset(str))
	{
		printf("export: \'%s\': not a valid identifier\n", str);
		*exit_stat = 1;
		*i += 1;
	}
	else
	{
		tmp = (*paths)->exp_struct;
		pos = 0;
		while (tmp)
		{
			check_tmp_exp(tmp, &f);
			if (!ft_strncmp(tmp->exp, str, f) && (ft_strlen(str) == f))
				break ;
			pos++;
			tmp = tmp->next;
		}
		remove_node_exp(paths, pos);
		*i += 1;
	}
}

void	unset_env_list(t_path **paths, char *str, int *i)
{
	t_env	*tmp;
	int		pos;

	if (!valid_unset(str))
		*i += 1;
	else
	{
		tmp = (*paths)->env_struct;
		pos = 0;
		while (tmp)
		{
			if (!ft_strncmp(str, tmp->env, ft_strlen(str)))
				break ;
			pos++;
			tmp = tmp->next;
		}
		remove_node_env(paths, pos);
		*i += 1;
	}
}

void	unset_cmd(char **str, t_path **paths, t_shl *shl)
{
	int	i;
	int	exit_stat;

	exit_stat = 0;
	i = 1;
	if (str[1] == NULL)
		return ;
	while (str[i])
		unset_exp_list(paths, str[i], &i, &exit_stat);
	i = 1;
	while (str[i])
		unset_env_list(paths, str[i], &i);
	shl->e_stat = exit_stat;
}
