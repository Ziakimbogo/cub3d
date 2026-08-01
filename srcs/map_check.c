/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gechavia <gechavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by gechavia          #+#    #+#             */
/*   Updated: 2026/07/17 03:17:20 by gechavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

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
