/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 07:48:48 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/01/29 04:18:45 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstclear_path(t_path **lst)
{
	t_path	*node;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		node = (*lst)->next;
		free((*lst)->pwd);
		free((*lst)->pwd_old);
		free((*lst));
		*lst = node;
	}
}

void	ft_lstclear_env(t_env **lst)
{
	t_env	*node;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		node = (*lst)->next;
		free((*lst)->env);
		free((*lst));
		*lst = node;
	}
}

void	ft_lstclear_exp(t_exp **lst)
{
	t_exp	*node;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		node = (*lst)->next;
		free((*lst)->exp);
		free((*lst));
		*lst = node;
	}
}
