/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 07:52:44 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/01/29 04:19:54 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tree	*init_cmd_node(char **cmd)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
	if (!node)
		print_exit(ERR_MALLOC);
	node->type = NODE_CMD;
	*cmd = remove_qoutes(*cmd);
	node->data.cmd = *cmd;
	if (!node->data.cmd)
		print_exit(ERR_MALLOC);
	node->left = NULL;
	node->right = NULL;
	node->level = 1;
	node->pos = 'm';
	return (node);
}

t_tree	*init_args_node(char **args, char *cmd)
{
	t_tree	*node;
	char	**arguments;

	node = malloc(sizeof(t_tree));
	if (!node)
		(free(cmd), free(*args), print_exit(ERR_MALLOC));
	node->type = NODE_ARG;
	strip_spaces(args);
	arguments = split_args(*args);
	if (!arguments)
		(free(cmd), free(*args), print_exit(ERR_MALLOC));
	free_str(args);
	node->data.args = arguments;
	node->left = NULL;
	node->right = NULL;
	node->level = 1;
	node->pos = 'm';
	return (node);
}

char	*exp_after_redir_node(char *str, char *first_half, int start)
{
	char	*second_half;
	char	*left_exp;

	while (str[start] == ' ')
		start++;
	while (str[start])
	{
		if (str[start] == '"' || str[start] == '\'')
		{
			start = inside_qoutes(str[start], str, start);
			continue ;
		}
		if (str[start] == ' ' || str[start] == '<' || str[start] == '>')
			break ;
		start++;
	}
	second_half = ft_substr(str, start, ft_strlen(str));
	if (!second_half)
		(free(str), print_exit(ERR_MALLOC));
	left_exp = ft_strjoin(first_half, second_half);
	free(second_half);
	if (!left_exp)
		(free(str), print_exit(ERR_MALLOC));
	return (left_exp);
}

char	*extract_file_name(char *str, int start)
{
	int		store_start;
	char	*file_name;

	store_start = start;
	while (str[start] == ' ')
		start++;
	while (start < ft_strlen(str))
	{
		if (str[start] == '"' || str[start] == '\'')
		{
			start = inside_qoutes(str[start], str, start);
			continue ;
		}
		if (str[start] == ' ' || str[start] == '>' || str[start] == '<')
			break ;
		start++;
	}
	file_name = ft_substr(str, store_start, start - store_start);
	if (!file_name)
		print_exit(ERR_MALLOC);
	strip_spaces(&file_name);
	if (ft_strlen(file_name) == 0)
		return (free(file_name), NULL);
	strip_spaces(&file_name);
	return (remove_qoutes(file_name));
}
