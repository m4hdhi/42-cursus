/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 07:52:39 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/01/29 04:19:51 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tree	*init_log_op_node(char spl_op)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
	if (!node)
		print_exit(ERR_MALLOC);
	node->type = NODE_LOG_OP;
	if (spl_op == '&')
		node->data.log_op = ft_strdup("&&");
	else if (spl_op == '|')
		node->data.log_op = ft_strdup("||");
	if (node->data.log_op == NULL)
		print_exit(ERR_MALLOC);
	return (node);
}

t_tree	*init_op_node(char op, char *str)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
	if (!node)
		return (free(str), print_exit(ERR_MALLOC), NULL);
	node->type = NODE_OP;
	node->data.op = op;
	node->left = NULL;
	node->right = NULL;
	node->level = 1;
	node->pos = 'm';
	return (node);
}

t_tree	*init_redir_node(char *redir)
{
	t_tree	*node;

	if (!redir)
		print_exit(ERR_MALLOC);
	node = malloc(sizeof(t_tree));
	if (!node)
		(free(redir), print_exit(ERR_MALLOC));
	node->type = NODE_REDIR;
	node->data.redir = redir;
	node->left = NULL;
	node->right = NULL;
	node->level = 1;
	node->pos = 'm';
	return (node);
}

t_tree	*init_file_node(char *str)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
	if (!node)
		print_exit(ERR_MALLOC);
	node->type = NODE_FILE;
	node->data.file = str;
	if (!node->data.file)
		print_exit(ERR_MALLOC);
	node->left = NULL;
	node->right = NULL;
	node->level = 1;
	node->pos = 'm';
	return (node);
}

t_tree	*init_exp_node(char **str)
{
	t_tree	*node;

	strip_spaces(str);
	if (ft_strlen(*str) == 0)
		return (free_str(str), NULL);
	node = malloc(sizeof(t_tree));
	if (!node)
		(free(*str), print_exit(ERR_MALLOC));
	node->type = NODE_EXP;
	node->data.exp = *str;
	if (!node->data.exp)
		(free(*str), print_exit(ERR_MALLOC));
	node->left = NULL;
	node->right = NULL;
	node->level = 1;
	node->pos = 'm';
	return (node);
}
