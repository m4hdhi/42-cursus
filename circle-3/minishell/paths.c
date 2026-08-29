/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 07:53:34 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/01/29 04:20:17 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cwd(void)
{
	char	cwd[1024];
	char	*res;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		write(2, "error\n", 6);
	res = new_path(cwd, 0);
	return (res);
}

t_path	*int_cd(void)
{
	t_path	*node_new;
	char	*str1;
	char	*str2;

	str1 = get_cwd();
	str2 = get_cwd();
	node_new = (t_path *)malloc(sizeof(t_path));
	if (node_new == NULL)
		return (NULL);
	node_new->pwd = str1;
	node_new->pwd_old = str2;
	node_new->next = NULL;
	return (node_new);
}

t_path	*init_paths(char **env)
{
	t_path	*paths;

	paths = int_cd();
	if (!paths)
		print_exit(ERR_MALLOC);
	paths->env_struct = int_env(env);
	if (!paths->env_struct)
	{
		paths->env_struct = NULL;
		appending_env(&paths->env_struct, ft_strjoin("PWD=", paths->pwd));
		appending_env(&paths->env_struct, ft_strdup("SHLVL=1"));
	}
	paths->exp_struct = int_exp(env);
	if (!paths->exp_struct)
	{
		paths->exp_struct = NULL;
		ap_exp(&paths->exp_struct, ft_strjoin("PWD=", paths->pwd));
		ap_exp(&paths->exp_struct, ft_strdup("SHLVL=1"));
	}
	return (paths);
}

int	list_length_env(t_env *env_list)
{
	int	len;

	len = 0;
	while (env_list)
	{
		len++;
		env_list = env_list->next;
	}
	return (len);
}
