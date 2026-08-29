/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 04:05:09 by mosami            #+#    #+#             */
/*   Updated: 2026/01/29 04:17:40 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ap_env(t_env **env, char *res)
{
	t_env	*temp;

	temp = malloc(sizeof(t_env));
	if (!temp)
		return ;
	temp->env = res;
	temp->next = NULL;
	if (*env)
		lstlast_env(*env)->next = temp;
	else
		*env = temp;
}

void	export_t_env(t_path **paths, char *tmp_char, char *sep, char *str)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = (*paths)->env_struct;
	while (str[i] != '=' && str[i])
		i++;
	if (i == ft_strlen(str))
		return ;
	while (tmp)
	{
		if (!ft_strncmp(tmp_char, tmp->env, ft_strlen(tmp_char)))
		{
			free(tmp->env);
			tmp->env = ft_strjoin(tmp_char, sep);
			return ;
		}
		tmp = tmp->next;
	}
	ap_env(&(*paths)->env_struct, ft_strjoin(tmp_char, sep));
}

void	export_t_exp(t_path **paths, char *tmp_char, char *sep, char *str)
{
	t_exp	*tmp;
	int		check;
	char	*joined_str;
	int		f;
	int		tmp_char_len;

	tmp = (*paths)->exp_struct;
	joined_str = ft_strjoin(tmp_char, sep);
	while (tmp)
	{
		f = 0;
		checker_which_mode(str, tmp_char, &check, &tmp_char_len);
		while (tmp->exp[f] != '=' && tmp->exp[f])
			f++;
		if (!ft_strncmp(tmp->exp, tmp_char, f) && (f == tmp_char_len))
		{
			exp_loop(tmp, joined_str, check);
			return ;
		}
		tmp = tmp->next;
	}
	append_check_equals(paths, str, joined_str, check);
}

t_exp	*int_exp(char **env)
{
	t_exp	*node_new;
	int		i;

	i = 1;
	if (!env || !env[0])
		return (NULL);
	node_new = (t_exp *)malloc(sizeof(t_exp));
	if (node_new == NULL)
		return (NULL);
	node_new->exp = ft_strdup(env[0]);
	if (!node_new->exp)
		return (NULL);
	node_new->next = NULL;
	while (env[i])
		ap_exp(&node_new, env[i++]);
	return (node_new);
}

void	export_cmd(char **str, t_path **paths, t_shl *shl)
{
	char	**sep;
	int		i;
	int		check_for_plus;
	int		e_stat;

	e_stat = 0;
	i = 1;
	if (!ft_strncmp("export", str[0], 7) && str[1] == NULL)
		exp_print(paths, 0);
	else if (!ft_strncmp("export", str[0], 7) && str[1] != NULL)
	{
		while (str[i])
		{
			str[i] = remove_qoutes(str[i]);
			check_for_plus = plus_equals_check(str[i]);
			sep = separator(str[i], check_for_plus);
			check_sep_export(sep, &i, &e_stat);
			if (!check_for_plus && sep)
				normal_export(paths, sep, str[i], &i);
			else if (check_for_plus && sep)
				plus_equals_export(paths, sep, &i);
		}
	}
	shl->e_stat = e_stat;
}
