/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gechavia <gechavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 16:28:57 by gechavia          #+#    #+#             */
/*   Updated: 2026/07/17 03:16:28 by gechavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	on_keypress(int keycode, t_data *d)
{
	if (keycode == K_ESC)
		close_program(d);
	else if (keycode == K_W)
		d->keys.w = 1;
	else if (keycode == K_A)
		d->keys.a = 1;
	else if (keycode == K_S)
		d->keys.s = 1;
	else if (keycode == K_D)
		d->keys.d = 1;
	else if (keycode == K_LEFT)
		d->keys.left = 1;
	else if (keycode == K_RIGHT)
		d->keys.right = 1;
	return (0);
}

int	on_keyrelease(int keycode, t_data *d)
{
	if (keycode == K_W)
		d->keys.w = 0;
	else if (keycode == K_A)
		d->keys.a = 0;
	else if (keycode == K_S)
		d->keys.s = 0;
	else if (keycode == K_D)
		d->keys.d = 0;
	else if (keycode == K_LEFT)
		d->keys.left = 0;
	else if (keycode == K_RIGHT)
		d->keys.right = 0;
	return (0);
}

int	on_destroy(t_data *d)
{
	close_program(d);
	return (0);
}
