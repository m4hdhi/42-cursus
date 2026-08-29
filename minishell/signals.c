/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 07:53:41 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/01/29 04:20:20 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*signal_checkpoint(t_std_fds *std_fds, t_shl *shl)
{
	char	*input;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	input = readline("minishell> ");
	if (!input)
	{
		write(2, "exit\n", 5);
		reset_std_fds(std_fds);
		free_array(shl->env);
		cleanup_shell(shl, TNT);
		exit(EXIT_SUCCESS);
	}
	if (g_signal_caught == SIGINT)
		shl->e_stat = 1;
	return (input);
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal_caught = SIGINT;
	}
}

void	handle_signals(int status, t_shl *shl)
{
	if (WTERMSIG(status) == SIGQUIT)
		write(2, "Quit: 3\n", 9);
	else if (WTERMSIG(status) == SIGSEGV)
		write(2, "Segmentation fault: 11\n", 24);
	shl->e_stat = WTERMSIG(status) + 128;
}

void	signal_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
