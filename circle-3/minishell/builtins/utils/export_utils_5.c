/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 04:04:22 by mosami            #+#    #+#             */
/*   Updated: 2026/01/29 04:17:18 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	checker_which_mode(char *str, char *tmp_char, int *check,
		int *tmp_char_len)
{
	int	i;
	int	g;

	i = 0;
	g = 0;
	*check = 1;
	while (str[i] != '=' && str[i])
		i++;
	if (i == ft_strlen(str))
		*check = 0;
	while (tmp_char[g] != '=' && tmp_char[g])
		g++;
	if (tmp_char[g] == '=')
		*tmp_char_len = ft_strlen(tmp_char) - 1;
	else
		*tmp_char_len = ft_strlen(tmp_char);
}

void	append_check_equals(t_path **paths, char *only_str, char *joined_str,
		int check)
{
	char	*str_only_malloc;

	str_only_malloc = ft_strdup(only_str);
	if (!check)
		ap_exp(&(*paths)->exp_struct, str_only_malloc);
	else
		ap_exp(&(*paths)->exp_struct, joined_str);
	(free(joined_str), free(str_only_malloc));
}

void	exp_loop(t_exp *tmp, char *joined_str, int check)
{
	if (!check)
	{
		free(joined_str);
		return ;
	}
	else
	{
		free(tmp->exp);
		tmp->exp = joined_str;
	}
}

void	check_sep_export(char **sep, int *i, int *e_stat)
{
	if (!sep)
	{
		*i += 1;
		*e_stat = 1;
	}
}
