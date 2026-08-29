/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 07:47:17 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/01/29 04:18:02 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_builtin(t_tree *tree, t_path *paths, t_shl *shl)
{
	char	**args;

	args = array_dup(tree->left->data.args);
	if (!ft_strncmp(tree->data.cmd, "echo", 5))
		echo_cmd(args, shl);
	else if (!ft_strncmp(tree->data.cmd, "pwd", 4))
		pwd_cmd(args, shl, &paths);
	else if (!ft_strncmp(tree->data.cmd, "cd", 3))
		cd_cmd(args, &paths, shl);
	else if (!ft_strncmp(tree->data.cmd, "export", 7))
		export_cmd(tree->left->data.args, &paths, shl);
	else if (!ft_strncmp(tree->data.cmd, "unset", 6))
		unset_cmd(args, &paths, shl);
	else if (!ft_strncmp(tree->data.cmd, "env", 4))
		env_cmd(args, &paths, shl);
	else if (!ft_strncmp(tree->data.cmd, "exit", 5))
		exit_cmd(args, shl);
	free_array(args);
}

void	handle_cmd(t_tree *tree, char **env, int pipe_flag, t_shl *shl)
{
	pid_t	pid;
	int		status;
	char	**args;

	args = array_dup(tree->left->data.args);
	if (!pipe_flag)
	{
		signal(SIGINT, SIG_IGN);
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
		{
			signal_default();
			cleanup_shell(shl, TNT);
			execute(args, env);
		}
		free_array(args);
		waitpid(pid, &status, 0);
		shl->e_stat = WEXITSTATUS(status);
		if (WIFSIGNALED(status) != 0)
			handle_signals(status, shl);
	}
	else
		(cleanup_shell(shl, TNT), execute(args, env));
}

void	handle_redir(t_tree *tree, char **env, int pipe_flag, t_shl *shl)
{
	int	fd;

	fd = 0;
	if (ft_strncmp(tree->data.redir, "<", 2) == 0)
		fd = handle_input_redir(tree->right->data.file, shl);
	else if (ft_strncmp(tree->data.redir, ">", 2) == 0)
		fd = handle_output_redir(tree->right->data.file, shl);
	else if (ft_strncmp(tree->data.redir, ">>", 2) == 0)
		fd = handle_append_redir(tree->right->data.file, shl);
	else if (ft_strncmp(tree->data.redir, "<<", 2) == 0)
		fd = handle_here_doc(tree->right->data.here_doc);
	if (fd != -1)
	{
		close(fd);
		gallows(tree->left, env, pipe_flag, shl);
	}
	else
		shl->e_stat = 1;
	if (pipe_flag)
	{
		(free_array(shl->env), cleanup_shell(shl, TNT));
		if (fd == -1)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
}

void	handle_pipe(t_tree *tree, char **env, t_shl *shl)
{
	pid_t	pid_left;
	pid_t	pid_right;
	int		pipefd[2];
	int		status;

	signal(SIGINT, SIG_IGN);
	if (pipe(pipefd) == -1)
	{
		(free_array(shl->env), cleanup_shell(shl, TNT));
		print_exit(ERR_PIPE);
	}
	pid_left = left_pipe(pipefd, tree, shl, env);
	pid_right = right_pipe(pipefd, tree, shl, env);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &status, 0);
	shl->e_stat = WEXITSTATUS(status);
	if (WIFSIGNALED(status) != 0)
		handle_signals(status, shl);
	if (tree->level != 1)
	{
		(free_array(shl->env), cleanup_shell(shl, TNT));
		exit(WEXITSTATUS(status));
	}
}

int	handle_here_doc(int read_from)
{
	dup2(read_from, 0);
	close(read_from);
	return (read_from);
}
