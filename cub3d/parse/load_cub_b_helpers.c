/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_cub_b_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 16:16:36 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/11 00:36:17 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line/get_next_line.h"

void	lc_handle_first_line(t_mapstate *st, char *ln)
{
	if (st->first)
	{
		strip_utf8_bom_inplace(ln);
		st->first = 0;
	}
}

int	lc_final_checks_and_finalize(t_game *g, t_build *b, t_parsef *f)
{
	if (!lc_require_all_ids(f))
		return (parse_error_rows(b->rows, b->y, "missing identifier(s)"));
	if (b->y == 0)
		return (parse_error_rows(b->rows, b->y, "no map after identifiers"));
	if (b->spawns != 1)
		return (parse_error_rows(b->rows, b->y, "missing player spawn"));
	return (lc_finalize_map(g, b));
}
