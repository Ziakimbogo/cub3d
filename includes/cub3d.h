/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catrenet <catrenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 16:28:56 by gechavia          #+#    #+#             */
/*   Updated: 2026/08/02 11:26:10 by catrenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "libft.h"
# include "get_next_line.h"

# define WIN_W 1280
# define WIN_H 720
# define TITLE "cub3D"

# define K_ESC    65307
# define K_W      119
# define K_A      97
# define K_S      115
# define K_D      100
# define K_LEFT   65361
# define K_RIGHT  65363

# define EV_KEYPRESS    2
# define EV_KEYRELEASE  3
# define EV_DESTROY     17
# define M_KEYPRESS     1L
# define M_KEYRELEASE   2L
# define M_DESTROY      131072L

# define TEX_NO		1
# define TEX_SO		2
# define TEX_WE		3
# define TEX_EA		4
# define TEX_COUNT	5

# define MOVE_SPEED	0.01
# define ROTATE_SPEED	0.01

# define COL_RADIUS 0.2

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_map
{
	char	**data;
	int		width;
	int		height;
}	t_map;

typedef struct s_config
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor;
	int		ceiling;
}	t_config;

typedef struct s_tmp
{
	char	**lines;
	char	**parts;
	char	*val;
	char	*tok;
}	t_tmp;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_keys		keys;
	t_config	cfg;
	t_map		map;
	t_tmp		tmp;
	int			player_x;
	int			player_y;
	char		player_dir;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	t_img		tex[TEX_COUNT];
}	t_data;

typedef struct s_ray
{
	int		grid_x;
	int		grid_y;
	int		step_x;
	int		step_y;
	int		side;
	int		wall_h;
	int		draw_start;
	int		draw_end;
	int		texture_id;
	double	dir_x;
	double	dir_y;
	double	cell_dist_x;
	double	cell_dist_y;
	double	next_cell_x;
	double	next_cell_y;
	double	perp_dist;
	double	wall_tex_x;
}	t_ray;

int		init_window(t_data *d);
int		close_program(t_data *d);

int		on_keypress(int keycode, t_data *d);
int		on_keyrelease(int keycode, t_data *d);
int		on_destroy(t_data *d);

void	put_pixel(t_img *img, int x, int y, int color);
int		render_frame(t_data *d);

int		parse_map(char *file, t_data *data);
void	strip_newline(char *s);
char	**read_file_lines(int fd);

char	*skip_spaces(char *s);
int		line_is_empty(char *s);
int		get_element_id(char *s);
int		process_lines(t_data *data, char **lines);

void	parse_element(t_data *data, char *line);

int		parse_color(t_data *data, char *s);

void	build_map(t_data *data, char **lines, int start);

int		check_map(t_data *data);

void	move_player(t_data *data);

void	init_player(t_data *d);

void	cast_ray(t_data *d, t_ray *ray, int x);

void	load_textures(t_data *d);
void	tex_and_wallx(t_data *d, t_ray *ray);
int		tex_color(t_data *d, t_ray *ray, int tex_x, int tex_y);

void	error_exit(t_data *data, char *msg);
void	free_lines(char **arr);
int		get_sign(double a, double b);

#endif
