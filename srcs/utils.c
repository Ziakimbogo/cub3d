/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catrenet <catrenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by gechavia          #+#    #+#             */
/*   Updated: 2026/07/21 10:53:59 by catrenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_lines(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/* free texture stockés dans la config */
static void	free_config(t_data *data)
{
	free(data->cfg.no);
	free(data->cfg.so);
	free(data->cfg.we);
	free(data->cfg.ea);
}

/* Affiche "Error\n<msg>\n", libère la map et la config, puis quitte */
void	error_exit(t_data *data, char *msg)
{
	ft_putstr_fd("Error\n", 2);
	if (msg)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
	}
	if (data)
	{
		free_lines(data->map.data);
		free_config(data);
	}
	exit(1);
}

int	get_sign(double a, double b)
{
	if (a > b)
		return (1);
	return (-1);
}

