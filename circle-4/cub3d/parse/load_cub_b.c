/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_cub_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 16:16:43 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/11 00:36:20 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line/get_next_line.h"

static int	lc_process_before_map(t_game *g, char *ln, t_parsef *f, int *go_map)
{
	int	r;

	if (is_blank_line_strict(ln))
		return (2);
	r = parse_cfg_line(g, ln, f);
	if (r == 2)
		return (2);
	if (r == 0)
	{
		if (!lc_require_all_ids(f))
			return (-1);
		*go_map = 1;
		return (1);
	}
	if (r == -2)
		return (parse_error(g, "duplicate identifier"), -1);
	if (r < 0)
		return (parse_error(g, "invalid identifier value"), -1);
	return (2);
}

static int	lc_handle_map_or_append(t_game *g, t_build *b,
					t_mapstate *st, char *ln)
{
	int	r;

	st->y = b->y;
	r = lc_validate_line_or_err(g, ln, st);
	if (r == 0)
		return (-1);
	if (r == 2)
		return (2);
	if (!lc_append_row_and_scan(g, b, ln))
		return (-1);
	return (1);
}

static int	lc_process_line_ctx(t_lcctx *ctx)
{
	int	r;

	strip_newline_cr(*ctx->ln);
	lc_handle_first_line(ctx->st, *ctx->ln);
	if (!ctx->st->in_map)
	{
		r = lc_process_before_map(ctx->g, *ctx->ln, ctx->f, &ctx->st->in_map);
		if (r == -1)
			return (0);
		if (r == 2)
			return (1);
	}
	r = lc_handle_map_or_append(ctx->g, ctx->b, ctx->st, *ctx->ln);
	if (r == -1)
	{
		free_rows_array(ctx->b->rows, ctx->b->y);
		ctx->b->rows = NULL;
		return (0);
	}
	(void)ctx->fd;
	return (1);
}

static int	loop_lines(int fd, t_game *g)
{
	char		*ln;
	t_build		b;
	t_parsef	f;
	t_mapstate	st;
	t_lcctx		ctx;

	b.rows = NULL;
	b.y = 0;
	b.cap = 0;
	b.maxw = 0;
	b.spawns = 0;
	f = (t_parsef){0, 0, 0, 0, 0, 0};
	st = (t_mapstate){0, 0, 0, 1};
	ln = get_next_line(fd);
	while (ln)
	{
		ctx = (t_lcctx){fd, g, &b, &f, &st, &ln};
		if (!lc_process_line_ctx(&ctx))
			return (free(ln), 0);
		free(ln);
		ln = get_next_line(fd);
	}
	if (!lc_final_checks_and_finalize(g, &b, &f))
		return (0);
	return (1);
}

int	load_cub(t_game *g, const char *path)
{
	int	fd;
	int	ok;

	if (!str_ends_with(path, ".cub"))
		return (write(2, "Error\nwrong file extension\n", 28), 0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (write(2, "Error\ncannot open or read file\n", 32), 0);
	ok = loop_lines(fd, g);
	close(fd);
	if (!ok)
		free_cfg_fields(&g->cfg);
	return (ok);
}
