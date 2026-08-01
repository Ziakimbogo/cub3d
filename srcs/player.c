/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catrenet <catrenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 15:17:51 by catrenet          #+#    #+#             */
/*   Updated: 2026/07/18 13:58:40 by catrenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_north(t_data *d)
{
	d->dir_x = 0;
	d->dir_y = -1;
	d->plane_x = 0.66;
	d->plane_y = 0;
}

static void	init_south(t_data *d)
{
	d->dir_x = 0;
	d->dir_y = 1;
	d->plane_x = -0.66;
	d->plane_y = 0;
}

static void	init_west(t_data *d)
{
	d->dir_x = -1;
	d->dir_y = 0;
	d->plane_x = 0;
	d->plane_y = -0.66;
}

static void	init_east(t_data *d)
{
	d->dir_x = 1;
	d->dir_y = 0;
	d->plane_x = 0;
	d->plane_y = 0.66;
}

void	init_player(t_data *d)
{
	d->pos_x = d->player_x + 0.5;
	d->pos_y = d->player_y + 0.5;
	if (d->player_dir == 'N')
		init_north(d);
	else if (d->player_dir == 'S')
		init_south(d);
	else if (d->player_dir == 'E')
		init_east(d);
	else if (d->player_dir == 'W')
		init_west(d);
}
