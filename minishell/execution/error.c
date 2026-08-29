/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 07:46:53 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/01/29 04:17:50 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_error(int code)
{
	if (code == ERR_FORMAT)
		write(2, "Error: Wrong format\n", 21);
	else if (code == ERR_EXECVE)
		write(2, "Error: Execve() failed\n", 24);
	else if (code == ERR_FILE)
		write(2, "Error: File or directory related\n", 34);
	else if (code == ERR_MALLOC)
		write(2, "Error: Malloc Failed!\n", 23);
	return (1);
}

void	print_exit(int code)
{
	if (code == ERR_MALLOC)
		write(2, "Error: Malloc Failed!\n", 23);
	else if (code == ERR_FORK)
		write(2, "Error: Fork() failed\n", 22);
	else if (code == ERR_PIPE)
		write(2, "Error: Pipe() failed\n", 22);
	else if (code == ERR_CMD)
		(write(2, "Error: cmd not found\n", 22), exit(127));
	else if (code == ERR_READLINE)
		write(2, "Readline failed!\n", 18);
	else if (code == ERR_DUP)
		write(2, "dup() or dup2() failed!\n", 25);
	exit(EXIT_FAILURE);
}

void	free_str(char **str)
{
	free(*str);
	*str = NULL;
}
