/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catrenet <catrenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by gechavia          #+#    #+#             */
/*   Updated: 2026/07/22 13:31:12 by gechavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_texture(t_data *data, char **slot, char *val)
{
	int	fd;

	if (*slot)
		error_exit(data, "Duplicate texture identifier");
	if (!val || !*val)
		error_exit(data, "Empty texture path");
	fd = open(val, O_RDONLY);
	if (fd < 0)
		error_exit(data, "Cannot open texture file");
	close(fd);
	*slot = val;
}

static void	set_color(t_data *data, int id, char *val)
{
	int	color;

	color = parse_color(data, val);
	if (id == 5)
	{
		if (data->cfg.floor != -1)
			error_exit(data, "Duplicate floor color");
		data->cfg.floor = color;
	}
	else
	{
		if (data->cfg.ceiling != -1)
			error_exit(data, "Duplicate ceiling color");
		data->cfg.ceiling = color;
	}
}

void	parse_element(t_data *data, char *line)
{
	int		id;
	int		len;
	char	*val;

	id = get_element_id(line);
	if (id <= 4)
		len = 2;
	else
		len = 1;
	val = ft_strtrim(line + len, " \t");
	if (!val)
		error_exit(data, "Malloc failed");
	data->tmp.val = val;
	if (id == 1)
		set_texture(data, &data->cfg.no, val);
	else if (id == 2)
		set_texture(data, &data->cfg.so, val);
	else if (id == 3)
		set_texture(data, &data->cfg.we, val);
	else if (id == 4)
		set_texture(data, &data->cfg.ea, val);
	else
	{
		set_color(data, id, val);
		free(val);
	}
	data->tmp.val = NULL;
}
