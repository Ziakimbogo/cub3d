#include "cub3d.h"

/* Crée la connexion, la fenêtre et l'image de travail unique.
   Retourne 0 en cas d'échec (chaque étape mlx peut renvoyer NULL). */
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

/* Libération propre : image, fenêtre, display, contexte.
   mlx_destroy_display + free(mlx) sont specifiques Linux. */
int	close_program(t_data *d)
{
	if (d->img.ptr)
		mlx_destroy_image(d->mlx, d->img.ptr);
	if (d->win)
		mlx_destroy_window(d->mlx, d->win);
	if (d->mlx)
	{
		mlx_destroy_display(d->mlx);
		free(d->mlx);
	}
	exit(0);
	return (0);
}
