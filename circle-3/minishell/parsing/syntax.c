/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 07:52:21 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/01/29 04:19:43 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_log_op_node(t_tree *node)
{
	if ((*node->left->data.exp) && (*node->right->data.exp))
		return (1);
	return (0);
}

int	check_op_node(t_tree *node)
{
	if (node->left != NULL && node->right != NULL)
	{
		if (!ft_strncmp(node->left->data.exp, "|", 2))
			return (0);
		return (1);
	}
	return (0);
}

int	check_redir_node(t_tree *node)
{
	if (!ft_strncmp(node->data.exp, "><", 2))
		return (0);
	if (!ft_strncmp(node->data.exp, "<>", 2))
		return (0);
	if (node->right != NULL)
	{
		if (!ft_strncmp(node->right->data.exp, "<", 2))
			return (0);
		else if (!ft_strncmp(node->right->data.exp, ">", 2))
			return (0);
		else if (!ft_strncmp(node->right->data.exp, "<<", 3))
			return (0);
		else if (!ft_strncmp(node->right->data.exp, ">>", 3))
			return (0);
		else if (!ft_strncmp(node->right->data.exp, "<>", 3))
			return (0);
		else if (!ft_strncmp(node->right->data.exp, "><", 3))
			return (0);
		else if (!ft_strncmp(node->right->data.exp, "|", 2))
			return (0);
		return (1);
	}
	return (0);
}

int	syntax_checker(t_tree *tree)
{
	if (tree->left != NULL)
		if (!syntax_checker(tree->left))
			return (0);
	if (tree->right != NULL)
		if (!syntax_checker(tree->right))
			return (0);
	if (tree->type == NODE_REDIR)
		return (check_redir_node(tree));
	else if (tree->type == NODE_OP)
		return (check_op_node(tree));
	else
		return (1);
}
