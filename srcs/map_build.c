/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catrenet <catrenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by gechavia          #+#    #+#             */
/*   Updated: 2026/08/02 16:11:54 by catrenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* last non-empty line index */
static int	find_map_end(char **lines, int start)
{
	int	end;
	int	i;

	end = start;
	i = start;
	while (lines[i])
	{
		if (!line_is_empty(lines[i]))
			end = i;
		i++;
	}
	return (end);
}

/* calc longest line */
static int	max_width(char **lines, int start, int end)
{
	int	width;
	int	len;
	int	i;

	width = 0;
	i = start;
	while (i <= end)
	{
		len = ft_strlen(lines[i]);
		if (len > width)
			width = len;
		i++;
	}
	return (width);
}

/* copy + pad line with 0 to width */
static char	*dup_padded(t_data *data, char *src, int width)
{
	char	*row;
	int		i;

	row = (char *)malloc(width + 1);
	if (!row)
		error_exit(data, "Malloc failed");
	i = 0;
	while (src[i])
	{
		row[i] = src[i];
		i++;
	}
	while (i < width)
		row[i++] = ' ';
	row[i] = '\0';
	return (row);
}

/* build rect map */
void	build_map(t_data *data, char **lines, int start)
{
	int	end;
	int	i;

	end = find_map_end(lines, start);
	i = start;
	while (i <= end)
	{
		if (line_is_empty(lines[i]))
			error_exit(data, "Empty line inside map");
		i++;
	}
	data->map.height = end - start + 1;
	data->map.width = max_width(lines, start, end);
	data->map.data = (char **)ft_calloc(data->map.height + 1, sizeof(char *));
	if (!data->map.data)
		error_exit(data, "Malloc failed");
	i = 0;
	while (i < data->map.height)
	{
		data->map.data[i] = dup_padded(data, lines[start + i], data->map.width);
		i++;
	}
}
