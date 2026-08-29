/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 04:02:56 by mosami            #+#    #+#             */
/*   Updated: 2026/01/29 04:15:43 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_lstadd_back_path(t_path **lst, t_path *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
		ft_lstlast_path(*lst)->next = new;
	else
		*lst = new;
}

void	add_env_pwd(t_path **paths, t_path *new, char *path_name)
{
	t_env	*tmp_env;

	tmp_env = (*paths)->env_struct;
	while (tmp_env)
	{
		if (!ft_strncmp(tmp_env->env, "PWD=", 4))
		{
			free(tmp_env->env);
			tmp_env->env = ft_strjoin(path_name, new->pwd);
			return ;
		}
		tmp_env = tmp_env->next;
	}
}

void	add_new_pwd(t_path **paths, t_path *new)
{
	t_exp	*tmp_exp;
	char	*path_name;

	path_name = ft_strdup("PWD=");
	tmp_exp = (*paths)->exp_struct;
	add_env_pwd(paths, new, path_name);
	while (tmp_exp)
	{
		if (!ft_strncmp(tmp_exp->exp, "PWD=", 4))
		{
			free(tmp_exp->exp);
			tmp_exp->exp = ft_strjoin(path_name, new->pwd);
			free(path_name);
			return ;
		}
		tmp_exp = tmp_exp->next;
	}
	free(path_name);
	return ;
}

void	add_old_pwd(t_path **paths, t_path *new)
{
	t_env	*tmp;
	char	*path_name;
	t_env	*old_pwd;

	path_name = ft_strdup("OLDPWD=");
	tmp = (*paths)->env_struct;
	old_pwd = malloc(sizeof(t_env));
	while (tmp)
	{
		if (!ft_strncmp(tmp->env, "OLDPWD=", 7))
		{
			free(tmp->env);
			tmp->env = ft_strjoin(path_name, new->pwd_old);
			free(path_name);
			free(old_pwd);
			return ;
		}
		tmp = tmp->next;
	}
	old_pwd->env = ft_strjoin(path_name, new->pwd_old);
	old_pwd->next = NULL;
	check_env_null(paths, old_pwd);
	free(path_name);
	return ;
}

void	add_old_pwd_exp(t_path **paths, t_path *new)
{
	t_exp	*tmp;
	char	*path_name;
	t_exp	*old_pwd;

	path_name = ft_strdup("OLDPWD=");
	tmp = (*paths)->exp_struct;
	old_pwd = malloc(sizeof(t_env));
	while (tmp)
	{
		if (!ft_strncmp(tmp->exp, "OLDPWD=", 7))
		{
			free(tmp->exp);
			tmp->exp = ft_strjoin(path_name, new->pwd_old);
			free(path_name);
			free(old_pwd);
			return ;
		}
		tmp = tmp->next;
	}
	old_pwd->exp = ft_strjoin(path_name, new->pwd_old);
	old_pwd->next = NULL;
	check_exp_null(paths, old_pwd);
	free(path_name);
	return ;
}
