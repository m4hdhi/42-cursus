/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 04:03:22 by mosami            #+#    #+#             */
/*   Updated: 2026/01/29 04:16:53 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_append(t_path **paths, char *res, t_shl *shl)
{
	t_path	*temp;
	char	*old_path;
	char	*new_path;

	old_path = ft_strdup(ft_lstlast_path(*paths)->pwd);
	new_path = ft_strdup(res);
	temp = malloc(sizeof(t_path));
	if (!temp)
		return ;
	temp->pwd = new_path;
	temp->pwd_old = old_path;
	temp->next = NULL;
	(add_new_pwd(paths, temp), add_old_pwd(paths, temp));
	add_old_pwd_exp(paths, temp);
	ft_lstadd_back_path(paths, temp);
	g_signal_caught = 0;
	shl->e_stat = 0;
}

void	append_switch_struct(t_path **paths, t_path **temp)
{
	*temp = malloc(sizeof(t_path));
	if (!temp)
		return ;
	(*temp)->pwd = ft_strdup(ft_lstlast_path(*paths)->pwd_old);
	(*temp)->pwd_old = ft_strdup(ft_lstlast_path(*paths)->pwd);
	(*temp)->next = NULL;
}

t_path	*ft_lstlast_path(t_path *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_env	*lstlast_env(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

int	check_old_pwd(t_path **paths)
{
	t_env	*tmp;

	tmp = (*paths)->env_struct;
	while (tmp)
	{
		if (!ft_strncmp(tmp->env, "OLDPWD=", 7))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
