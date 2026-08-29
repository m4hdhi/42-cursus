/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 07:54:09 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/01/29 04:20:05 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shl	*init_shell(t_path *paths)
{
	t_shl		*shl;

	shl = malloc(sizeof(t_shl));
	if (!shl)
		print_exit(ERR_MALLOC);
	shl->paths = paths;
	shl->e_stat = 0;
	shl->inside_pipe = FALSE;
	shl->head = NULL;
	shl->env = NULL;
	return (shl);
}

void	dup_fds(t_std_fds *std_fds)
{
	std_fds->std_in = dup(STDIN_FILENO);
	std_fds->std_out = dup(STDOUT_FILENO);
	std_fds->std_err = dup(STDERR_FILENO);
}

void	reset_std_fds(t_std_fds *std_fds)
{
	dup2(std_fds->std_in, STDIN_FILENO);
	dup2(std_fds->std_out, STDOUT_FILENO);
	dup2(std_fds->std_err, STDERR_FILENO);
}
