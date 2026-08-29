/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 04:04:11 by mosami            #+#    #+#             */
/*   Updated: 2026/01/29 04:17:12 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	export_t_env_plus(t_path **paths, char *tmp_char, char *sep)
{
	t_env	*tmp;
	char	*holder;
	int		i;

	tmp = (*paths)->env_struct;
	while (tmp)
	{
		if (!ft_strncmp(tmp_char, tmp->env, ft_strlen(tmp_char)))
		{
			i = 0;
			holder = tmp->env;
			while (holder[i] != '=' && holder[i])
				i++;
			if (holder[i] == '\0')
				holder_is_equals_env(tmp, sep, tmp_char);
			else if (holder[i] != '\0')
				tmp->env = if_with_equals_env(tmp, holder, tmp_char, sep);
			return ;
		}
		tmp = tmp->next;
	}
	ap_env(&(*paths)->env_struct, ft_strjoin(tmp_char, sep));
}

void	export_t_exp_plus(t_path **paths, char *tmp_char, char *sep)
{
	t_exp	*tmp;
	char	*holder;
	int		i;
	int		f;
	int		tmp_char_len;

	tmp = (*paths)->exp_struct;
	while (tmp)
	{
		tmp_looper(&f, tmp, &tmp_char_len, tmp_char);
		if (!ft_strncmp(tmp->exp, tmp_char, f) && (f == tmp_char_len))
		{
			i = 0;
			holder = tmp->exp;
			while (holder[i] != '=' && holder[i])
				i++;
			if (holder[i] == '\0')
				holder_is_equals_exp(tmp, sep, tmp_char);
			else if (holder[i] != '\0')
				tmp->exp = if_with_equals_exp(tmp, holder, tmp_char, sep);
			return ;
		}
		tmp = tmp->next;
	}
	plus_append(paths, tmp_char, sep);
}

int	plus_equals_check(char *str)
{
	int	i;

	i = 0;
	if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')
		|| str[i] == '_')
		i++;
	else
		return (0);
	while (str[i])
	{
		if (str[i] == '+')
		{
			if (str[i + 1] == '=')
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (0);
}

void	plus_equals_export(t_path **paths, char **sep, int *i)
{
	char	*tmp_char;
	char	*new_str;

	new_str = ft_calloc(ft_strlen(sep[0]), sizeof(char *));
	ft_strlcpy(new_str, sep[0], ft_strlen(sep[0]));
	if (!sep)
		*i += 1;
	else
	{
		tmp_char = ft_strjoin(new_str, "=");
		export_t_exp_plus(paths, tmp_char, sep[1]);
		export_t_env_plus(paths, tmp_char, sep[1]);
		(free_array(sep), free(tmp_char), free(new_str));
		*i += 1;
	}
}

void	normal_export(t_path **paths, char **sep, char *str, int *i)
{
	char	*tmp_char;

	if (!sep)
		*i += 1;
	else
	{
		tmp_char = ft_strjoin(sep[0], "=");
		export_t_exp(paths, tmp_char, sep[1], str);
		export_t_env(paths, tmp_char, sep[1], str);
		(free_array(sep), free(tmp_char));
		*i += 1;
	}
}
