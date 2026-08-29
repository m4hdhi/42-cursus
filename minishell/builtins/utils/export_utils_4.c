/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 04:04:17 by mosami            #+#    #+#             */
/*   Updated: 2026/01/29 04:17:16 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*if_with_equals_env(t_env *tmp, char *holder, char *tmp_char, char *sep)
{
	char	*old_exp;
	char	*joined_str;
	char	*res_char;
	int		i;

	i = 0;
	while (holder[i] != '=' && holder[i])
		i++;
	if (holder[i] == '=')
	{
		i++;
		old_exp = ft_strdup(holder + i);
		free(tmp->env);
		joined_str = ft_strjoin(tmp_char, old_exp);
		res_char = ft_strjoin(joined_str, sep);
		free(old_exp);
		free(joined_str);
		return (res_char);
	}
	return (NULL);
}

void	holder_is_equals_env(t_env *tmp, char *sep, char *tmp_char)
{
	free(tmp->env);
	if (sep[0] != '\0')
		tmp->env = ft_strjoin(tmp_char, sep);
	else if (sep[0] == '\0')
		tmp->env = ft_strdup(tmp_char);
}

void	holder_is_equals_exp(t_exp *tmp, char *sep, char *tmp_char)
{
	free(tmp->exp);
	if (sep[0] != '\0')
		tmp->exp = ft_strjoin(tmp_char, sep);
	else if (sep[0] == '\0')
		tmp->exp = ft_strdup(tmp_char);
}

char	*if_with_equals_exp(t_exp *tmp, char *holder, char *tmp_char, char *sep)
{
	char	*old_exp;
	char	*joined_str;
	char	*res_char;
	int		i;

	i = 0;
	while (holder[i] != '=' && holder[i])
		i++;
	if (holder[i] == '=')
	{
		i++;
		old_exp = ft_strdup(holder + i);
		free(tmp->exp);
		joined_str = ft_strjoin(tmp_char, old_exp);
		res_char = ft_strjoin(joined_str, sep);
		free(old_exp);
		free(joined_str);
		return (res_char);
	}
	return (NULL);
}

void	exp_print(t_path **paths, int i)
{
	t_exp	*tmp;
	char	*check;
	int		check_with_equals;

	tmp = (*paths)->exp_struct;
	sorted_exp(&tmp);
	while (tmp)
	{
		i = 0;
		while (tmp->exp[i] != '=' && tmp->exp[i])
			i++;
		check = checker_print(tmp, &i, &check_with_equals);
		if (check_with_equals && i)
			printf("declare -x %.*s=\"%s\"\n", (int)(check - tmp->exp),
				tmp->exp, check + 1);
		else
			printf("declare -x %s\n", tmp->exp);
		tmp = tmp->next;
	}
}
