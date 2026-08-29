/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 04:03:33 by mosami            #+#    #+#             */
/*   Updated: 2026/01/29 04:16:56 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_cwd(t_path **paths)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		write(2, "cd: error retrieving current directory: getcwd:", 48);
		write(2, "cannot access parent directories:", 34);
		write(2, " No such file or directory\n", 27);
		if (chdir((*paths)->pwd) == -1)
			return ;
	}
}

void	check_exp_null(t_path **paths, t_exp *old_pwd)
{
	if ((*paths)->exp_struct == NULL)
		(*paths)->exp_struct = old_pwd;
	else
		lstlast_exp((*paths)->exp_struct)->next = old_pwd;
}

void	check_env_null(t_path **paths, t_env *old_pwd)
{
	if ((*paths)->env_struct == NULL)
		(*paths)->env_struct = old_pwd;
	else
		lstlast_env((*paths)->env_struct)->next = old_pwd;
}

void	error_msg_access(void)
{
	write(2, "cd: ", 5);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 2);
}

char	*get_new_cwd(char *malloc_path)
{
	char	*res;
	char	curr_path[1024];

	chdir(malloc_path);
	getcwd(curr_path, sizeof(curr_path));
	res = ft_calloc(ft_strlen(curr_path) + 1, sizeof(char *));
	ft_strlcpy(res, curr_path, ft_strlen(curr_path) + 1);
	free(malloc_path);
	return (res);
}
