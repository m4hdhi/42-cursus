/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 04:05:14 by mosami            #+#    #+#             */
/*   Updated: 2026/01/29 04:17:43 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_curr_pwd(t_path **paths)
{
	t_exp	*tmp_exp;
	char	*holder;

	tmp_exp = (*paths)->exp_struct;
	while (tmp_exp)
	{
		if (!ft_strncmp(tmp_exp->exp, "PWD=", 4))
		{
			holder = ft_strchr(tmp_exp->exp, '=');
			return (holder + 1);
		}
		tmp_exp = tmp_exp->next;
	}
	return (NULL);
}

void	pwd_cmd(char **str, t_shl *shl, t_path **paths)
{
	char	cwd[1024];

	if (!ft_strncmp(str[0], "pwd", 3))
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			printf("%s\n", cwd);
			g_signal_caught = 0;
			shl->e_stat = 0;
		}
		else
		{
			printf("%s\n", find_curr_pwd(paths));
			return ;
		}
	}
}
