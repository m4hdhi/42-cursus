/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 16:18:42 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/07/11 00:36:57 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "minilibx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIN_W 1024
# define WIN_H 768
# define FOV 0.66
# define MOVE_SPEED 0.08
# define COLL_PAD 0.2
# define ROT_SPEED 0.045
# define MOUSE_SENS_X 0.003
# define MOUSE_SENS_Y_RAD 0.003
# define PITCH_MAX_RAD 1.5533430342749532
# define PITCH_MIN_RAD -1.5533430342749532
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

typedef struct s_img
{
	void		*ptr;
	char		*addr;
	int			bpp;
	int			line;
	int			endian;
	int			w;
	int			h;
}				t_img;

typedef struct s_tex
{
	t_img		img;
}				t_tex;

typedef struct s_map
{
	char		**grid;
	int			w;
	int			h;
}				t_map;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		pitch_ang;
}				t_player;

typedef struct s_keys
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			left;
	int			right;
}				t_keys;

typedef struct s_cfg
{
	int			floor_rgb;
	int			ceil_rgb;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
}				t_cfg;

typedef struct s_mlx
{
	void		*ptr;
	void		*win;
	t_img		frame;
}				t_mlx;

typedef struct s_game
{
	t_mlx		mlx;
	t_cfg		cfg;
	t_map		map;
	t_tex		tex[4];
	t_player	pl;
	t_keys		keys;
	int			mouse_captured;
	int			center_x;
	int			center_y;
	int			mouse_dx;
	int			mouse_dy;
}				t_game;

typedef struct s_pt
{
	int			y;
	int			x;
}				t_pt;

typedef struct s_parsef
{
	int			no;
	int			so;
	int			we;
	int			ea;
	int			f;
	int			c;
}				t_parsef;

typedef struct s_build
{
	char		**rows;
	int			y;
	int			cap;
	int			maxw;
	int			spawns;
}				t_build;

typedef struct s_mapstate
{
	int			in_map;
	int			ended;
	int			y;
	int			first;
}				t_mapstate;

typedef struct s_rayhit
{
	double		walld;
	int			ori;
	double		wx;
}				t_rayhit;

typedef struct s_col
{
	int			top;
	int			bot;
	int			tex_id;
	double		tex_x;
}				t_col;

typedef struct s_rect
{
	int			y;
	int			x;
	int			w;
	int			h;
	size_t		rows;
	size_t		cols;
}				t_rect;

typedef struct s_dda
{
	double		ddx;
	double		ddy;
	double		sdx;
	double		sdy;
	int			side;
	int			mx;
	int			my;
}				t_dda;

typedef struct s_stack
{
	t_pt		*buf;
	size_t		sp;
	size_t		cap;
}				t_stack;

typedef struct s_lcctx
{
	int			fd;
	t_game		*g;
	t_build		*b;
	t_parsef	*f;
	t_mapstate	*st;
	char		**ln;
}				t_lcctx;

typedef struct s_rdir
{
	double		x;
	double		y;
}				t_rdir;

/* core */
int				load_cub(t_game *g, const char *path);
int				validate_map(t_map *m);
int				game_init(t_game *g);
void			game_destroy(t_game *g, const char *msg, int ec);
void			draw_frame(t_game *g);
int				raycast_cell(t_game *g, double rdx, double rdy, t_rayhit *hit);

/* input/hooks */
int				key_press(int key, void *p);
int				key_release(int key, void *p);
int				on_close(void *p);
int				mouse_move_handle(t_game *g);
int				mouse_motion_hook(int x, int y, void *p);
int				expose_redraw(void *p);
int				game_loop(void *param);
void			handle_move(t_game *g);
int				can_move(t_game *g, double nx, double ny);
void			rotate_left_right(t_game *g);

/* utils */
void			free_split(char **s);
int				is_space(int c);
int				str_ends_with(const char *s, const char *suf);
int				is_blank_line_strict(const char *s);
void			strip_newline_cr(char *s);
void			strip_utf8_bom_inplace(char *s);
void			free_rows_array(char **rows, int count);
int				safe_mul_size(size_t a, size_t b, size_t *out);

/* parsing */
int				parse_cfg_line(t_game *g, char *line, t_parsef *f);
int				lc_append_row_and_scan(t_game *g, t_build *b, char *ln);
int				lc_finalize_map(t_game *g, t_build *b);
int				lc_validate_line_or_err(t_game *g, char *ln, t_mapstate *st);
int				lc_require_all_ids(t_parsef *f);
int				validate_map_line_chars(const char *s);
void			free_cfg_fields(t_cfg *c);
int				parse_error(t_game *g, const char *msg);
int				parse_error_rows(char **rows, int y, const char *msg);
int				parse_id_path(char **dst, char *line, const char *id);

/* render */
void			put_px(t_img *img, int x, int y, int color);
int				sample_tex(t_tex *t, double tx, double ty);
void			draw_column_tex(t_game *g, int x, t_col c);
void			draw_column_flat_wrap(t_game *g, int x, int pitchi);
int				flood_touch_floor(char **p, int pw, int ph);
int				clamp_mid(int mid);
void			draw_ceiling_until(t_game *g, int x, int endy);
void			draw_floor_from(t_game *g, int x, int starty);
void			draw_column_flat(t_game *g, int x, int pitchi);
void			init_dda(t_game *g, t_rdir d, t_dda *st);

int				color_from_csv(const char *s, int *rgb);
int				parse_color_csv(int *dst, char *line, const char *id);
int				lc_final_checks_and_finalize(t_game *g, t_build *b,
					t_parsef *f);
void			lc_handle_first_line(t_mapstate *st, char *ln);

#endif
