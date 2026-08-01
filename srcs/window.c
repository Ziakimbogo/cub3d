/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gechavia <gechavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 03:23:50 by gechavia          #+#    #+#             */
/*   Updated: 2026/07/29 21:30:16 by gechavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_window(t_data *d)
{
	d->mlx = mlx_init();
	if (!d->mlx)
		return (0);
	d->win = mlx_new_window(d->mlx, WIN_W, WIN_H, TITLE);
	if (!d->win)
		return (0);
	d->img.ptr = mlx_new_image(d->mlx, WIN_W, WIN_H);
	if (!d->img.ptr)
		return (0);
	d->img.addr = mlx_get_data_addr(d->img.ptr, &d->img.bpp,
			&d->img.line_len, &d->img.endian);
	if (!d->img.addr)
		return (0);
	return (1);
}

int	close_program(t_data *d)
{
	int	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		if (d->tex[i].ptr)
			mlx_destroy_image(d->mlx, d->tex[i].ptr);
		i++;
	}
	if (d->img.ptr)
		mlx_destroy_image(d->mlx, d->img.ptr);
	if (d->win)
		mlx_destroy_window(d->mlx, d->win);
	if (d->mlx)
	{
		mlx_destroy_display(d->mlx);
		free(d->mlx);
	}
	free_lines(d->map.data);
	free(d->cfg.no);
	free(d->cfg.so);
	free(d->cfg.we);
	free(d->cfg.ea);
	exit(0);
	return (0);
}
