/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catrenet <catrenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 16:28:56 by gechavia          #+#    #+#             */
/*   Updated: 2026/08/02 17:09:26 by catrenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

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

/* find correct column of image for this x */
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
