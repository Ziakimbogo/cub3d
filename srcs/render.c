/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gechavia <gechavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 16:28:56 by gechavia          #+#    #+#             */
/*   Updated: 2026/07/17 03:23:05 by gechavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Ecrit un pixel dans le buffer image. Offset = y*line_len + x*(bpp/8).
   color format 0x00RRGGBB. Merci l'IA ;) j'aurais pas trouvé tt seul */
void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

/* plafond sur la moitie haute, sol sur la moitie basse.*/
static void	fill_background(t_data *d)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < WIN_H)
	{
		if (y < WIN_H / 2)
			color = 0x2288CC;
		else
			color = 0x333333;
		x = 0;
		while (x < WIN_W)
		{
			put_pixel(&d->img, x, y, color);
			x++;
		}
		y++;
	}
}

/* Appele en boucle par mlx_loop_hook. Ordre à faire pour le fonctionnement :
	lire les flags   et deplacer le joueur, puis dessiner la frame, puis print l'image. */
int	render_frame(t_data *d)
{
	/* appliquer le mouvement d->keys  */
	fill_background(d);
	mlx_put_image_to_window(d->mlx, d->win, d->img.ptr, 0, 0);
	return (0);
}
