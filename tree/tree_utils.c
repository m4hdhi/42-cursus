/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 07:52:59 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/01/29 04:20:01 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_array(char **array)
{
	int	len;

	len = 0;
	while (array[len])
		len++;
	return (len);
}

void	add_node(t_tree **tree, t_tree *node, int side)
{
	if (!node)
		return ;
	if (*tree == NULL)
	{
		*tree = node;
		return ;
	}
	if ((*tree)->left == NULL && side == LEFT)
		(*tree)->left = node;
	else if ((*tree)->right == NULL)
		(*tree)->right = node;
}
