/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 07:47:43 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/01/29 04:18:08 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	here_docs_ahead(t_tree *tree)
{
	int	result;

	result = FALSE;
	if (tree->type == NODE_REDIR && ft_strncmp(tree->data.redir, "<<", 2) == 0)
		result = TRUE;
	if (tree->left != NULL)
		result = here_docs_ahead(tree->left);
	if (!result)
		if (tree->right != NULL)
			result = here_docs_ahead(tree->right);
	return (result);
}

int	find_docs(t_tree *tree, t_shl *shl)
{
	pid_t	pid;
	int		status;
	int		result;

	g_signal_caught = 0;
	if (tree == NULL)
		return (1);
	result = 1;
	if (tree->type == NODE_REDIR && ft_strncmp(tree->data.redir, "<<", 2) == 0)
	{
		tree->right->data.here_doc = ft_hdoc(tree->right->data.exp, shl, &pid);
		waitpid(pid, &status, 0);
		tree->right->type = NODE_HDOC;
		if (WEXITSTATUS(status) == 1)
			return (shl->e_stat = 1, close(tree->right->data.here_doc), FALSE);
		if (tree->left != NULL)
			if (here_docs_ahead(tree->left) == TRUE)
				close(tree->right->data.here_doc);
	}
	result = find_docs(tree->left, shl);
	if (result)
		result = find_docs(tree->right, shl);
	return (result);
}

static void	handle_heredoc_sig(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_caught = SIGINT;
		close(STDIN_FILENO);
	}
}

static void	read_write(char *limiter, int write_to, t_env *env, t_shl *shl)
{
	char	*new_line;
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (line)
		{
			if (!ft_strncmp(line, limiter, ft_strlen(limiter) + 1))
				break ;
			new_line = ft_strjoin(line, "\n");
			new_line = env_expansion(new_line, env, shl);
			write(write_to, new_line, ft_strlen(new_line));
			free_str(&new_line);
			free_str(&line);
		}
		free_str(&line);
	}
	close(write_to);
}

int	ft_hdoc(char *limiter, t_shl *shl, pid_t *pid)
{
	int	doc_pipe[2];

	if (pipe(doc_pipe) == -1)
	{
		close(doc_pipe[1]);
		close(doc_pipe[0]);
		print_error(ERR_PIPE);
	}
	*pid = fork();
	if (*pid == -1)
		(free_array(shl->env), cleanup_shell(shl, TNT), print_exit(ERR_FORK));
	if (*pid == 0)
	{
		signal(SIGINT, handle_heredoc_sig);
		signal(SIGQUIT, SIG_IGN);
		read_write(limiter, doc_pipe[1], shl->paths->env_struct, shl);
		close(doc_pipe[0]);
		free_array(shl->env);
		cleanup_shell(shl, TNT);
		exit(g_signal_caught == SIGINT);
	}
	close(doc_pipe[1]);
	free(limiter);
	return (doc_pipe[0]);
}
