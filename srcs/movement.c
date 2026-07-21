/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catrenet <catrenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 13:45:05 by catrenet          #+#    #+#             */
/*   Updated: 2026/07/21 09:16:09 by catrenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_sign(double a, double b)
{
	if (a > b)
		return (1);
	return (-1);
}

// move only if not a wall
static void	try_move(t_data *d, double new_x, double new_y)
{
	int		sign_x;
	int		sign_y;
	double	check_x;
	double	check_y;

	sign_x = get_sign(new_x, d->pos_x);
	sign_y = get_sign(new_y, d->pos_y);
	check_x = new_x + sign_x * COL_RADIUS;
	check_y = new_y + sign_y * COL_RADIUS;
	if (d->map.data[(int)d->pos_y][(int)check_x] != '1')
		d->pos_x = new_x;
	if (d->map.data[(int)check_y][(int)d->pos_x] != '1')
		d->pos_y = new_y;
}

static void	move_forward(t_data *d, double dir)
{
	double	new_x;
	double	new_y;

	new_x = d->pos_x + d->dir_x * MOVE_SPEED * dir;
	new_y = d->pos_y + d->dir_y * MOVE_SPEED * dir;
	try_move(d, new_x, new_y);
}

static void	move_sideways(t_data *d, double dir)
{
	double	new_x;
	double	new_y;

	new_x = d->pos_x - d->dir_y * MOVE_SPEED * dir;
	new_y = d->pos_y + d->dir_x * MOVE_SPEED * dir;
	try_move(d, new_x, new_y);
}

static void	rotate_player(t_data *d, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = d->dir_x;
	d->dir_x = d->dir_x * cos(angle) - d->dir_y * sin(angle);
	d->dir_y = old_dir_x * sin(angle) + d->dir_y * cos(angle);
	old_plane_x = d->plane_x;
	d->plane_x = d->plane_x * cos(angle) - d->plane_y * sin(angle);
	d->plane_y = old_plane_x * sin(angle) + d->plane_y * cos(angle);
}

void	move_player(t_data *data)
{
	if (data->keys.w)
		move_forward(data, 1.0);
	if (data->keys.s)
		move_forward(data, -1.0);
	if (data->keys.d)
		move_sideways(data, 1.0);
	if (data->keys.a)
		move_sideways(data, -1.0);
	if (data->keys.left)
		rotate_player(data, -ROTATE_SPEED);
	if (data->keys.right)
		rotate_player(data, ROTATE_SPEED);
}
