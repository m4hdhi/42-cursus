/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 04:04:31 by mosami            #+#    #+#             */
/*   Updated: 2026/01/29 04:17:21 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	tmp_looper(int *f, t_exp *tmp, int *tmp_char_len, char *tmp_char)
{
	int	g;

	g = 0;
	*f = 0;
	while (tmp->exp[*f] != '=' && tmp->exp[*f])
		*f += 1;
	while (tmp_char[g] != '=' && tmp_char[g])
		g++;
	if (tmp_char[g] == '=')
		*tmp_char_len = ft_strlen(tmp_char) - 1;
	else
		*tmp_char_len = ft_strlen(tmp_char);
}

void	plus_append(t_path **paths, char *tmp_char, char *sep)
{
	char	*joined_str;

	joined_str = ft_strjoin(tmp_char, sep);
	ap_exp(&(*paths)->exp_struct, joined_str);
	free(joined_str);
}
