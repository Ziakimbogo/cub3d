/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catrenet <catrenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 10:08:50 by catrenet          #+#    #+#             */
/*   Updated: 2026/08/02 17:03:46 by catrenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* calc from player direction + camera plane, set starting cell */
static void	init_ray_direction(t_data *data, t_ray *ray, int i)
{
	double	camera_plane;

	camera_plane = 2.0 * i / (double)WIN_W - 1.0;
	ray->dir_x = data->dir_x + data->plane_x * camera_plane;
	ray->dir_y = data->dir_y + data->plane_y * camera_plane;
	ray->grid_x = (int)data->pos_x;
	ray->grid_y = (int)data->pos_y;
	if (ray->dir_x == 0)
		ray->cell_dist_x = 1e30;
	else
		ray->cell_dist_x = fabs(1.0 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->cell_dist_y = 1e30;
	else
		ray->cell_dist_y = fabs(1.0 / ray->dir_y);
}

/* step direction (+1/-1) per axis + initial distance to next grid line */
static void	step_next_grid(t_data *data, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->next_cell_x = (data->pos_x - ray->grid_x) * ray->cell_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->next_cell_x = (ray->grid_x + 1.0 - data->pos_x) * ray->cell_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->next_cell_y = (data->pos_y - ray->grid_y) * ray->cell_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->next_cell_y = (ray->grid_y + 1.0 - data->pos_y) * ray->cell_dist_y;
	}
}

/* step to closest grid line x or y */
static void	dda_algo(t_data *data, t_ray *ray)
{
	int	line;

	line = 0;
	while (!line)
	{
		if (ray->next_cell_x < ray->next_cell_y)
		{
			ray->next_cell_x += ray->cell_dist_x;
			ray->grid_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->next_cell_y += ray->cell_dist_y;
			ray->grid_y += ray->step_y;
			ray->side = 1;
		}
		if (data->map.data[ray->grid_y][ray->grid_x] == '1')
			line = 1;
	}
}

/* perpendicular dist to avoid fisheye distortion */
static void	wall_height(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_dist = ray->next_cell_x - ray->cell_dist_x;
	else
		ray->perp_dist = ray->next_cell_y - ray->cell_dist_y;
	ray->wall_h = (int)(WIN_H / ray->perp_dist);
	ray->draw_start = -ray->wall_h / 2 + WIN_H / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->wall_h / 2 + WIN_H / 2;
	if (ray->draw_end >= WIN_H)
		ray->draw_end = WIN_H - 1;
}

void	cast_ray(t_data *data, t_ray *ray, int x)
{
	init_ray_direction(data, ray, x);
	step_next_grid(data, ray);
	dda_algo(data, ray);
	wall_height(ray);
}
