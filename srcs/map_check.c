/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catrenet <catrenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by gechavia          #+#    #+#             */
/*   Updated: 2026/08/02 17:22:05 by catrenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* check if floor or player direction */
static int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/* check if map is closed */
static int	cell_open(t_data *data, int x, int y)
{
	char	**g;

	g = data->map.data;
	if (x == 0 || y == 0 || x == data->map.width - 1
		|| y == data->map.height - 1)
		return (1);
	if (g[y - 1][x] == ' ' || g[y + 1][x] == ' '
		|| g[y][x - 1] == ' ' || g[y][x + 1] == ' ')
		return (1);
	return (0);
}

/* validate cell + record player pos */
static void	handle_cell(t_data *data, int x, int y, int *players)
{
	char	c;

	c = data->map.data[y][x];
	if (c == ' ' || c == '1')
		return ;
	if (!is_walkable(c))
		error_exit(data, "Invalid character in map");
	if (cell_open(data, x, y))
		error_exit(data, "Map is not closed by walls");
	if (c != '0')
	{
		data->player_x = x;
		data->player_y = y;
		data->player_dir = c;
		(*players)++;
	}
}

/* check only one player */
int	check_map(t_data *data)
{
	int	x;
	int	y;
	int	players;

	players = 0;
	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			handle_cell(data, x, y, &players);
			x++;
		}
		y++;
	}
	if (players != 1)
		error_exit(data, "Map must contain exactly one player");
	return (1);
}
