/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catrenet <catrenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 16:28:56 by gechavia          #+#    #+#             */
/*   Updated: 2026/07/28 11:31:32 by catrenet         ###   ########.fr       */
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

/* --- X11 keycodes (Linux). Sur Mac ils diffèrent, d'où les macros. --- */
# define K_ESC    65307
# define K_W      119
# define K_A      97
# define K_S      115
# define K_D      100
# define K_LEFT   65361
# define K_RIGHT  65363

/* --- X11 event codes / masks --- */
# define EV_KEYPRESS    2
# define EV_KEYRELEASE  3
# define EV_DESTROY     17
# define M_KEYPRESS     (1L << 0)
# define M_KEYRELEASE   (1L << 1)
# define M_DESTROY      (1L << 17)

/* texture indices */
# define TEX_NO		1
# define TEX_SO		2
# define TEX_WE		3
# define TEX_EA		4

/* move + rotation */
# define MOVE_SPEED	0.01
# define ROTATE_SPEED	0.01

/* collision */
# define COL_RADIUS 0.2

/* Déplacement touches 1 == touchés // 0 pas touchés. On les met à jour dans on_keypress et on_keyrelease.
   Lues chaque frame par le loop_hook -> mouvement fluide. */
typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

/* image mémoire */
typedef struct s_img
{
	void	*ptr; // pointeur vers l'image
	char	*addr; // buffer de pixels
	int		bpp; // bits par pixel
	int		line_len; // longueur d'une ligne en octets
	int		endian; // métaonneés calcul de l'endianness (boutisme) https://fr.wikipedia.org/wiki/Boutisme
	int		width;
	int	height; 
}	t_img;

/* Grille de la map : lignes avec des espaces, des 1, des 0, et un seul caractère de départ du joueur (N/S/E/W).
   largeur = ligne la plus longue, hauteur = nombre de lignes. */
typedef struct s_map
{
	char	**data;
	int		width;
	int		height;
}	t_map;

/* Couleurs au format 0x00RRGGBB, -1 tant qu'elles ne sont pas définies. */
typedef struct s_config
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor;
	int		ceiling;
}	t_config;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_keys		keys;
	t_config	cfg;
	t_map		map;
	int			player_x;
	int			player_y;
	char		player_dir;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	t_img		tex[4];
}	t_data;

typedef struct s_ray
{
	int		grid_x;
	int		grid_y;
	int		step_x;	// direction (+1 R/-1 L) along the grid
	int		step_y;	// direction (+1 U/-1 D) along the grid
	int		side;
	int		wall_h;
	int		draw_start;
	int		draw_end;
	int		texture_id;
	double	dir_x;	// player direction
	double	dir_y;
	double	cell_dist_x;	// distance to cross one full grid cell
	double	cell_dist_y;
	double	next_cell_x;	// distance to first grid line crossed
	double	next_cell_y;	
	double	perp_dist;
	double	wall_tex_x;
}	t_ray;

/* window.c */
int		init_window(t_data *d);
int		close_program(t_data *d);

/* events.c */
int		on_keypress(int keycode, t_data *d);
int		on_keyrelease(int keycode, t_data *d);
int		on_destroy(t_data *d);

/* render.c */
void	put_pixel(t_img *img, int x, int y, int color);
int		render_frame(t_data *d);

/* parsing.c */
int		parse_map(char *file, t_data *data);
void	strip_newline(char *s);
char	**read_file_lines(int fd);

/* parse_lines.c */
char	*skip_spaces(char *s);
int		line_is_empty(char *s);
int		get_element_id(char *s);
int		process_lines(t_data *data, char **lines);

/* parse_element.c */
void	parse_element(t_data *data, char *line);

/* parse_color.c */
int		parse_color(t_data *data, char *s);

/* map_build.c */
void	build_map(t_data *data, char **lines, int start);

/* map_check.c */
int		check_map(t_data *data);

/* movement.c */
void	move_player(t_data *data);

/* player.c */
void	init_player(t_data *d);

/* raycasting.h */
void	cast_ray(t_data *d, t_ray *ray, int x);

/* texture.c */
void	load_textures(t_data *d);
void	tex_and_wallx(t_data *d, t_ray *ray);
int		tex_color(t_data *d, t_ray *ray, int tex_x, int tex_y);

/* utils.c */
void	error_exit(t_data *data, char *msg);
void	free_lines(char **arr);
int		get_sign(double a, double b);

#endif
