/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gallows_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 07:47:02 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/01/29 04:17:57 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*set_own_path(char *cmd)
{
	if (ft_strchr(cmd, '/'))
		return (cmd);
	return (NULL);
}

static char	**extract_path_env(char **env)
{
	int		i;
	char	*path;
	char	**absoulute_paths;

	i = 0;
	path = NULL;
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(env[i] + 5);
			break ;
		}
		i++;
	}
	absoulute_paths = ft_split(path, ':');
	free(path);
	return (absoulute_paths);
}

char	*ft_cmd_exits(char **env, char *temp_cmd)
{
	char	**a_paths;
	char	*temp_str_join;
	char	*path;
	int		i;
	char	*cmd;

	path = NULL;
	cmd = temp_cmd;
	a_paths = extract_path_env(env);
	if (!cmd || set_own_path(cmd) || !a_paths)
		return (free_array(a_paths), ft_strdup(cmd));
	i = -1;
	while (a_paths[++i])
	{
		temp_str_join = ft_strjoin(a_paths[i], "/");
		free(a_paths[i]);
		a_paths[i] = ft_strjoin(temp_str_join, cmd);
		free(temp_str_join);
		if (access(a_paths[i], F_OK) == 0 && access(a_paths[i], X_OK) == 0)
		{
			path = ft_strdup(a_paths[i]);
			break ;
		}
	}
	return (free_array(a_paths), path);
}

char	**array_dup(char **array)
{
	int		i;
	int		j;
	char	**dup_array;

	i = 0;
	j = 0;
	if (!array)
		return (NULL);
	while (array[i])
		i++;
	dup_array = (char **)malloc(sizeof(char *) * (i + 1));
	if (!dup_array)
		return (NULL);
	while (j < i)
	{
		dup_array[j] = remove_qoutes(ft_strdup(array[j]));
		j++;
	}
	dup_array[i] = NULL;
	return (dup_array);
}
