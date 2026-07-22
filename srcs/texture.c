/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catrenet <catrenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 11:28:57 by catrenet          #+#    #+#             */
/*   Updated: 2026/07/21 10:47:09 by catrenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Load one XPM texture file into image struct
static void	load_one_texture(t_data *d, t_img *tex, char *path)
{
	tex->ptr = mlx_xpm_file_to_image(d->mlx, path, &tex->width, &tex->height);
	if (!tex->ptr)
		error_exit(d, "Failed to load texture");
	tex->addr = mlx_get_data_addr(tex->ptr, &tex->bpp, &tex->line_len,
			&tex->endian);
	if (!tex->addr)
		error_exit(d, "Failed to get texture data");
}

void	load_textures(t_data *d)
{
	load_one_texture(d, &d->tex[TEX_NO], d->cfg.no);
	load_one_texture(d, &d->tex[TEX_SO], d->cfg.so);
	load_one_texture(d, &d->tex[TEX_WE], d->cfg.we);
	load_one_texture(d, &d->tex[TEX_EA], d->cfg.ea);
}

// Pick correct textures to apply based on side + direction
static void	pick_texture(t_ray *ray)
{
	if (ray->side == 0) // hits vertical grid line ie E/W wall
	{
		if (ray->dir_x > 0)
			ray->texture_id = TEX_EA;
		else
			ray->texture_id = TEX_WE;
	}
	else // hits horizontal grid line
	{
		if (ray->dir_y > 0)
			ray->texture_id = TEX_SO;
		else
			ray->texture_id = TEX_NO;
	}
}

/* set spot on wall where ray hits (0.0 to 1.0) to pick column of texture */
void	tex_and_wallx(t_data *d, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_tex_x = d->pos_y + ray->perp_dist * ray->dir_y;
	else
		ray->wall_tex_x = d->pos_x + ray->perp_dist * ray->dir_x;
	ray->wall_tex_x -= floor(ray->wall_tex_x);
	pick_texture(ray);
}

int	tex_color(t_data *d, t_ray *ray, int tex_x, int tex_y)
{
	t_img	*tex;
	char	*pixel;

	tex = &d->tex[ray->texture_id];
	pixel = tex->addr + (tex_y * tex->line_len + tex_x * (tex->bpp / 8));
	return (*(unsigned int *)pixel);
}
