/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 04:05:00 by mosami            #+#    #+#             */
/*   Updated: 2026/01/29 04:17:34 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*last_env(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	appending_env(t_env **env, char *res)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->env = res;
	new_node->next = NULL;
	if (*env)
		last_env(*env)->next = new_node;
	else
		*env = new_node;
}

t_env	*int_env(char **env)
{
	t_env	*node_new;
	char	*str;
	int		i;

	i = 1;
	if (!env || !env[0])
		return (NULL);
	str = ft_strdup(env[0]);
	node_new = (t_env *)malloc(sizeof(t_env));
	if (!node_new)
		return (NULL);
	node_new->env = str;
	node_new->next = NULL;
	while (env[i])
		appending_env(&node_new, ft_strdup(env[i++]));
	return (node_new);
}

void	env_cmd(char **str, t_path **paths, t_shl *shl)
{
	t_env	*new_node;

	new_node = (*paths)->env_struct;
	if (str[1] != NULL)
	{
		write(2, "env: ", 6);
		write(2, &str[1], ft_strlen(str[1]));
		write(2, ":No such file or directory \n", 29);
		shl->e_stat = 127;
		return ;
	}
	while (new_node)
	{
		printf("%s\n", new_node->env);
		new_node = new_node->next;
	}
	g_signal_caught = 0;
	shl->e_stat = 0;
}
