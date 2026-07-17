/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gechavia <gechavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 16:28:56 by gechavia          #+#    #+#             */
/*   Updated: 2026/07/15 23:04:24 by gechavia         ###   ########.fr       */
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
}	t_data;

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

/* utils.c */
void	error_exit(t_data *data, char *msg);
void	free_lines(char **arr);

#endif
