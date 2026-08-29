/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 07:52:16 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/01/29 04:19:40 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	split_redirection(char *str, t_tree **node, int i)
{
	t_tree	*node_tmp;
	char	*cmd;
	char	*file_name;
	int		append;

	append = 0;
	if (str[i] == '<' || str[i] == '>')
	{
		if (str[i + 1] == '<' || str[i + 1] == '>')
			append = 1;
		node_tmp = *node;
		*node = init_redir_node(ft_substr(str, i, 1 + append));
		cmd = extract_cmd_from_redir(ft_substr(str, 0, i), str, i, append);
		if (cmd)
			add_node(node, init_exp_node(&cmd), LEFT);
		file_name = extract_file_name(str, i + 1 + append);
		if (file_name)
			add_node(node, init_file_node(file_name), RIGHT);
		free(str);
		free(node_tmp);
		if ((*node)->left != NULL)
			tokenizer(cmd, &(*node)->left);
		return (1);
	}
	return (0);
}

int	split_operator(char *str, t_tree **node, int i)
{
	t_tree	*node_tmp;
	char	*left_exp;
	char	*right_exp;

	if (str[i] == '|')
	{
		node_tmp = *node;
		*node = init_op_node(str[i], str);
		left_exp = ft_substr(str, 0, i);
		if (!left_exp)
			(free(str), print_exit(ERR_MALLOC));
		add_node(node, init_exp_node(&left_exp), LEFT);
		right_exp = ft_substr(str, i + 1, ft_strlen(str));
		if (!right_exp)
			(free(str), print_exit(ERR_MALLOC));
		add_node(node, init_exp_node(&right_exp), RIGHT);
		(free(str), free(node_tmp));
		if ((*node)->left != NULL)
			tokenizer(left_exp, &(*node)->left);
		if ((*node)->right != NULL)
			tokenizer(right_exp, &(*node)->right);
		return (1);
	}
	return (0);
}

int	split_cmd(char *str, int i, t_tree **node)
{
	char	*args;
	char	*cmd;
	t_tree	*node_tmp;

	if (str[i] == ' ' || str[i] == '\0')
	{
		node_tmp = *node;
		cmd = ft_substr(str, 0, i);
		if (!cmd)
			(free(str), print_exit(ERR_MALLOC));
		*node = init_cmd_node(&cmd);
		args = ft_substr(str, 0, ft_strlen(str));
		if (!args)
			(free(str), print_exit(ERR_MALLOC));
		add_node(node, init_args_node(&args, (*node)->data.cmd), LEFT);
		free(str);
		free(node_tmp);
		return (1);
	}
	return (0);
}

char	**split_args(char *str)
{
	char	**args;

	if (ft_strlen(str) == 0)
		return (NULL);
	args = malloc(sizeof(char *) * (count_args(str) + 5));
	if (!args)
		print_exit(ERR_MALLOC);
	create_args_array(str, &args);
	return (args);
}
