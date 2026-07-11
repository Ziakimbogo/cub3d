/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gechavia <gechavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 16:28:53 by gechavia          #+#    #+#             */
/*   Updated: 2026/07/11 16:41:05 by gechavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_extension(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 4)
		return (0);
	if (file[len - 4] == '.' && file[len - 3] == 'c'
		&& file[len - 2] == 'u' && file[len - 1] == 'b')
		return (1);
	return (0);
}

static int	check_one(int ac, char **av, t_data *data)
{
	if (ac != 2)
	{
		ft_putstr_fd("Error\nUsage: ./cub3d map.cub\n", 2);
		return (1);
	}
	if (!check_extension(av[1]))
	{
		ft_putstr_fd("Error\nMap must have .cub extension\n", 2);
		return (1);
	}
	ft_bzero(data, sizeof(t_data));
	if (!parse_map(av[1], data))
		error_exit(data, "Map parsing failed");
	if (!check_map(data))
		error_exit(data, "Invalid map");
	if (!check_path(data))
		error_exit(data, "No valid path in map");
	return (0);
}

// int	load_images(t_data *data)
// {
// 	if (!load_image(data, &data->wall, "textures/wall.xpm"))
// 		return (0);
// 	if (!load_image(data, &data->floor, "textures/floor.xpm"))
// 		return (0);
// 	if (!load_image(data, &data->player, "textures/player.xpm"))
// 		return (0);
// 	if (!load_image(data, &data->collect, "textures/collect.xpm"))
// 		return (0);
// 	if (!load_image(data, &data->exit, "textures/exit.xpm"))
// 		return (0);
// 	return (1);
// }

int	main(void)
{
	t_data	data;

	data = (t_data){0};
	if (check_one(argc, argv, &data))
		return (1);
	if (!init_window(&data))
	{
		write(2, "Error\nmlx init failed\n", 22);
		return (1);
	}
		// if (!load_images(&data))
		// error_exit(&data, "Loading images failed");
	mlx_hook(data.win, EV_KEYPRESS, M_KEYPRESS, on_keypress, &data);
	mlx_hook(data.win, EV_KEYRELEASE, M_KEYRELEASE, on_keyrelease, &data);
	mlx_hook(data.win, EV_DESTROY, M_DESTROY, on_destroy, &data);
	mlx_loop_hook(data.mlx, render_frame, &data);
	mlx_loop(data.mlx);
	return (0);
}