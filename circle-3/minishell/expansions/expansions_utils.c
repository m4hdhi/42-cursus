/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 07:47:56 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/01/29 04:18:13 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_args(t_tree **arg_node, t_env *env, t_shl *shl)
{
	int	i;

	i = 0;
	while ((*arg_node)->data.args[i])
	{
		(*arg_node)->data.args[i] = env_expansion((*arg_node)->data.args[i],
				env, shl);
		(*arg_node)->data.args[i] = remove_qoutes((*arg_node)->data.args[i]);
		i++;
	}
}

void	expansions(t_tree **tree, t_env *env, t_shl *shl)
{
	if ((*tree))
	{
		if ((*tree)->type == NODE_REDIR && ft_strncmp((*tree)->data.redir, "<<",
				2) == 0)
			(*tree)->right->type = NODE_LMTR;
		if ((*tree)->left != NULL)
			expansions(&(*tree)->left, env, shl);
		if ((*tree)->right != NULL)
			expansions(&(*tree)->right, env, shl);
		if ((*tree)->type == NODE_OP || (*tree)->type == NODE_LMTR)
			;
		else if ((*tree)->type == NODE_ARG)
			expand_args(tree, env, shl);
		else
			(*tree)->data.exp = env_expansion((*tree)->data.exp, env, shl);
	}
}

int	not_here_doc(char *str, int i)
{
	if (i == -1 || i == 0)
		return (1);
	while (str[i] == ' ')
	{
		i--;
		if (i == 0)
			return (1);
	}
	while (str[i] == '"' || str[i] == '\'')
	{
		i--;
		if (i == 0)
			return (1);
	}
	while (str[i] == ' ')
	{
		i--;
		if (i == 0)
			return (1);
	}
	if (i >= 1)
		if (str[i] == '<' && str[i - 1] == '<')
			return (0);
	return (1);
}

int	valid_expansion(char *str, int i)
{
	if (str[i] == '$' && ((str[i + 1] >= 'A' && str[i + 1] <= 'Z') || (str[i
					+ 1] >= 'a' && str[i + 1] <= 'z') || ((str[i + 1] >= '0'
					&& str[i + 1] <= '9')) || str[i + 1] == '?'))
	{
		return (TRUE);
	}
	return (FALSE);
}
