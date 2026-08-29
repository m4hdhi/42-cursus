/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gallows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 07:47:09 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/01/29 04:18:00 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute(char **cmd, char *env[])
{
	char		*path;
	struct stat	directory;

	if (ft_strlen(cmd[0]) == 0)
		(free_array(env), free_array(cmd), print_exit(ERR_CMD));
	path = ft_cmd_exits(env, cmd[0]);
	if (!path)
		(free_array(cmd), free_array(env), print_exit(ERR_CMD));
	execve(path, cmd, env);
	if (stat(path, &directory) == 0)
	{
		write(2, "Error\n", 6);
		(free(path), free_array(env));
		free_array(cmd);
		exit(126);
	}
	else if (ft_strchr(path, '/'))
	{
		write(2, "Error\n", 6);
		(free(path), free_array(env));
		free_array(cmd);
		exit(127);
	}
	(free(path), free_array(cmd), free_array(env));
	print_exit(ERR_CMD);
}

int	is_builtin(char *str)
{
	if (!ft_strncmp(str, "echo", 5) || !ft_strncmp(str, "cd", 3)
		|| !ft_strncmp(str, "pwd", 4) || !ft_strncmp(str, "export", 7)
		|| !ft_strncmp(str, "unset", 6) || !ft_strncmp(str, "env", 4)
		|| !ft_strncmp(str, "exit", 5))
	{
		return (1);
	}
	return (0);
}

int	gallows(t_tree *tree, char **env, int pipe_flag, t_shl *shl)
{
	if (tree == NULL)
		return (1);
	tree->level += 1;
	if (tree->type == NODE_OP)
		handle_pipe(tree, env, shl);
	else if (tree->type == NODE_REDIR)
		handle_redir(tree, env, pipe_flag, shl);
	else if (tree->type == NODE_CMD)
	{
		if (is_builtin(tree->data.cmd))
		{
			handle_builtin(tree, shl->paths, shl);
			if (pipe_flag)
			{
				free_array(shl->env);
				cleanup_shell(shl, TNT);
				exit(EXIT_SUCCESS);
			}
		}
		else
			handle_cmd(tree, env, pipe_flag, shl);
	}
	return (1);
}
