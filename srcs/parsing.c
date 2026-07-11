/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gechavia <gechavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 16:42:57 by gechavia          #+#    #+#             */
/*   Updated: 2026/07/11 16:43:20 by gechavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	count_row(char *line, t_game *game, int y)
{
	int	x;

	x = 0;
	while (x < game->map.width && line[x] && line[x] != '\n' && line[x] != '\r')
	{
		if (line[x] == 'C')
			game->map.collectibles++;
		else if (line[x] == 'E')
			game->map.exits++;
		else if (line[x] == 'P')
		{
			game->map.players++;
			game->player_x = x;
			game->player_y = y;
		}
		else if (line[x] != '0' && line[x] != '1')
			error_exit(game, "Invalid character in map");
		x++;
	}
}

static void	fill_map(int fd, t_game *game)
{
	char	*line;
	int		y;
	int		line_len;

	y = 0;
	line = get_next_line(fd);
	while (line)
	{
		line_len = ft_strlen(line);
		if (line_len > 0 && line[line_len - 1] == '\n')
			line_len--;
		if (line_len > 0 && line[line_len - 1] == '\r')
			line_len--;
		if (line_len != game->map.width)
		{
			free(line);
			error_exit(game, "Map is not rectangular");
		}
		game->map.data[y] = line;
		count_row(line, game, y);
		y++;
		line = get_next_line(fd);
	}
}

static void	ft_calc_map_width(t_game *game, int fd)
{
	char	*line;

	game->map.height = 0;
	line = get_next_line(fd);
	if (!line)
		error_exit(game, "Empty map");
	game->map.width = ft_strlen(line);
	if (game->map.width > 0 && line[game->map.width - 1] == '\n')
		game->map.width--;
	if (game->map.width > 0 && line[game->map.width - 1] == '\r')
		game->map.width--;
	if (game->map.width >= LIMIT_W)
		error_exit(game, "LIMITE ATTEINTE (largeur)");
	if (game->map.height >= LIMIT_H)
		error_exit(game, "LIMITE ATTEINTE (hauteur)");
	while (line)
	{
		game->map.height++;
		free(line);
		line = get_next_line(fd);
	}
}

int	parse_map(char *file, t_game *game)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nCannot open map file\n", 2);
		return (0);
	}
	ft_calc_map_width(game, fd);
	close(fd);
	game->map.data = (char **)ft_calloc(game->map.height, sizeof(char *));
	if (!game->map.data)
		error_exit(game, "Malloc failed");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit(game, "Cannot reopen map file");
	fill_map(fd, game);
	close(fd);
	return (1);
}