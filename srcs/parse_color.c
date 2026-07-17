/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gechavia <gechavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by gechavia          #+#    #+#             */
/*   Updated: 2026/07/17 03:17:34 by gechavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Compte les occurrences de c dans s */
static int	count_char(char *s, char c)
{
	int	n;

	n = 0;
	while (*s)
		if (*s++ == c)
			n++;
	return (n);
}

/* Convertit un composant "  220 " en entier 0-255 */
static int	component_value(t_data *data, char *tok)
{
	char	*t;
	int		i;
	int		v;

	t = ft_strtrim(tok, " \t");
	if (!t)
		error_exit(data, "Malloc failed");
	if (!*t)
		error_exit(data, "Color component is empty");
	i = 0;
	while (t[i])
	{
		if (t[i] < '0' || t[i] > '9')
			error_exit(data, "Color component is not a number");
		i++;
	}
	v = ft_atoi(t);
	free(t);
	if (v < 0 || v > 255)
		error_exit(data, "Color component out of range (0-255)");
	return (v);
}

/* Parse "R,G,B" en 0x00RRGGBB dans [0, 255] */
int	parse_color(t_data *data, char *s)
{
	char	**parts;
	int		rgb[3];
	int		i;

	if (count_char(s, ',') != 2)
		error_exit(data, "Color must be R,G,B");
	parts = ft_split(s, ',');
	if (!parts)
		error_exit(data, "Malloc failed");
	i = 0;
	while (i < 3)
	{
		if (!parts[i])
		{
			free_lines(parts);
			error_exit(data, "Color must be R,G,B");
		}
		rgb[i] = component_value(data, parts[i]);
		i++;
	}
	free_lines(parts);
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}
