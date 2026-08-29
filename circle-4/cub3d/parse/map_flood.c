/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_flood.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 16:17:05 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/11 00:36:25 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	stack_push_space(char **p, int y, int x, t_stack *st)
{
	p[y][x] = '#';
	st->buf[st->sp] = (t_pt){y, x};
	st->sp++;
}

static int	check_neighbor(char **p, int y, int x)
{
	if (p[y][x] == '0')
		return (1);
	if (p[y][x] == ' ')
		return (2);
	return (0);
}

static int	handle_neighbor(char **p, int y, int x, t_stack *st)
{
	int	rc;

	rc = check_neighbor(p, y, x);
	if (rc == 1)
		return (1);
	if (rc == 2)
		stack_push_space(p, y, x, st);
	return (0);
}

static int	flood_loop(char **p, int pw, int ph, t_stack *st)
{
	t_pt	cur;

	while (st->sp)
	{
		st->sp--;
		cur = st->buf[st->sp];
		if (cur.y - 1 >= 0 && handle_neighbor(p, cur.y - 1, cur.x, st))
			return (1);
		if (cur.y + 1 < ph && handle_neighbor(p, cur.y + 1, cur.x, st))
			return (1);
		if (cur.x - 1 >= 0 && handle_neighbor(p, cur.y, cur.x - 1, st))
			return (1);
		if (cur.x + 1 < pw && handle_neighbor(p, cur.y, cur.x + 1, st))
			return (1);
	}
	return (0);
}

int	flood_touch_floor(char **p, int pw, int ph)
{
	t_stack	st;
	size_t	cap;
	int		rc;

	cap = (size_t)pw * (size_t)ph;
	if (!cap)
		return (-1);
	st.buf = (t_pt *)malloc(cap * sizeof(t_pt));
	if (!st.buf)
		return (-1);
	st.sp = 0;
	st.cap = cap;
	p[0][0] = '#';
	st.buf[st.sp] = (t_pt){0, 0};
	st.sp++;
	rc = flood_loop(p, pw, ph, &st);
	free(st.buf);
	return (rc);
}
