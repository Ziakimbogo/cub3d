/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catrenet <catrenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 16:28:56 by gechavia          #+#    #+#             */
/*   Updated: 2026/07/18 17:36:05 by catrenet         ###   ########.fr       */
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

/* plafond sur la moitie haute, sol sur la moitie basse.
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
}*/

static void	draw_ceiling_floor(t_data *d, int x, t_ray *ray)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
	{
		put_pixel(&d->img, x, y, d->cfg.ceiling);
		y++;
	}
	y = ray->draw_end;
	while (y < WIN_H)
	{
		put_pixel(&d->img, x, y, d->cfg.floor);
		y++;
	}
}

static int	get_tex_x(t_data *d, t_ray *ray)
{
	int		tex_x;
	t_img	*tex;

	tex = &d->tex[ray->texture_id];
	tex_x = (int)(ray->wall_tex_x * (double)tex->width);
	if ((ray->side == 0 && ray->dir_x > 0) || (ray->side == 1
			&& ray->dir_y < 0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

static void	draw_column(t_data *d, t_ray *ray, int x)
{
	int		y;
	int		tex_x;
	int		tex_y;
	t_img	*tex;

	tex = &d->tex[ray->texture_id];
	tex_x = get_tex_x(d, ray);
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = ((y * 2 - WIN_H + ray->wall_h) * tex->height)
			/ (2 * ray->wall_h);
		put_pixel(&d->img, x, y, tex_color(d, ray, tex_x, tex_y));
		y++;
	}
}

/* Appele en boucle par mlx_loop_hook. Ordre à faire pour le fonctionnement :
	lire les flags   et deplacer le joueur, puis dessiner la frame, puis print l'image. */
int	render_frame(t_data *d)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIN_W)
	{
		cast_ray(d, &ray, x);
		tex_and_wallx(d, &ray);
		draw_ceiling_floor(d, x, &ray);
		draw_column(d, &ray, x);
		x++;
	}
	mlx_put_image_to_window(d->mlx, d->win, d->img.ptr, 0, 0);
	return (0);
}
