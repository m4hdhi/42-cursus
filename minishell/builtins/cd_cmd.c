/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 04:04:51 by mosami            #+#    #+#             */
/*   Updated: 2026/01/29 04:17:28 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*cd_resolve_path(char **str, char *cwd, t_path **paths, int *check)
{
	char	*res;

	res = NULL;
	if (!ft_strncmp(str[0], "cd", 3) && str[1] == NULL)
		res = get_home(paths);
	else if (!ft_strncmp(str[0], "cd", 3) && (!ft_strncmp(str[1], "~", 2)))
		res = get_home(paths);
	else if (str[1] != NULL && (!ft_strncmp(str[1], "..", 3)))
		res = new_path(cwd, 1);
	else if (str[1] != NULL && (!ft_strncmp(str[1], "-", 2)))
	{
		res = switch_cd(paths);
		*check = 1;
	}
	else if (str[1] != NULL)
		res = new_path(str[1], 0);
	return (res);
}

void	cd_cmd(char **str, t_path **paths, t_shl *shl)
{
	char	*res;
	int		check;
	char	cwd[1024];

	check = 0;
	getcwd(cwd, sizeof(cwd));
	if (str[1] != NULL && str[2] != NULL)
	{
		write(2, "cd: too many arguments\n", 24);
		shl->e_stat = 1;
		return ;
	}
	res = cd_resolve_path(str, cwd, paths, &check);
	if (check == 0 && res)
		ft_append(paths, res, shl);
	if (res)
		free(res);
}
