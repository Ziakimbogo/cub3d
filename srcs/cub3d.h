/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gechavia <gechavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 16:28:56 by gechavia          #+#    #+#             */
/*   Updated: 2026/07/11 16:50:41 by gechavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>

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

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_keys	keys;
}	t_data;

typedef struct s_map
{
	char	**data;
	int		width;
	int		height;
	int		collectibles;
	int		exits;
	int		players;
}	t_map;


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

#endif
