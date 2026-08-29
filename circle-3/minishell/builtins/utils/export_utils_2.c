/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 04:04:03 by mosami            #+#    #+#             */
/*   Updated: 2026/01/29 04:17:08 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_exp	*lstlast_exp(t_exp *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ap_exp(t_exp **exp, char *res)
{
	t_exp	*temp;

	temp = malloc(sizeof(t_exp));
	if (!temp)
		return ;
	temp->exp = ft_strdup(res);
	temp->next = NULL;
	if (*exp)
		lstlast_exp(*exp)->next = temp;
	else
		*exp = temp;
}

void	swap_node(t_exp *cur, t_exp *hold)
{
	char	*tmp;

	tmp = cur->exp;
	cur->exp = hold->exp;
	hold->exp = tmp;
}

void	sorted_exp(t_exp **head)
{
	int		swap;
	t_exp	*current;

	current = NULL;
	if (!(*head))
		return ;
	swap = 1;
	while (swap)
	{
		swap = 0;
		current = (*head);
		while (current->next)
		{
			if (ft_strncmp(current->exp, current->next->exp,
					ft_strlen(current->exp)) > 0)
			{
				swap_node(current, current->next);
				swap = 1;
			}
			current = current->next;
		}
	}
}

char	*checker_print(t_exp *tmp, int *i, int *check_with_equals)
{
	char	*check;

	check = NULL;
	if (*i == ft_strlen(tmp->exp))
		*check_with_equals = 0;
	else
	{
		*check_with_equals = 1;
		check = ft_strchr(tmp->exp, '=');
	}
	return (check);
}
