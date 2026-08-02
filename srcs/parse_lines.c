/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catrenet <catrenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by gechavia          #+#    #+#             */
/*   Updated: 2026/08/02 16:49:05 by catrenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*skip_spaces(char *s)
{
	while (*s == ' ' || *s == '\t')
		s++;
	return (s);
}

int	line_is_empty(char *s)
{
	return (*skip_spaces(s) == '\0');
}

/* identify line type */
int	get_element_id(char *s)
{
	if (!ft_strncmp(s, "NO", 2) && (s[2] == ' ' || s[2] == '\t' || !s[2]))
		return (1);
	if (!ft_strncmp(s, "SO", 2) && (s[2] == ' ' || s[2] == '\t' || !s[2]))
		return (2);
	if (!ft_strncmp(s, "WE", 2) && (s[2] == ' ' || s[2] == '\t' || !s[2]))
		return (3);
	if (!ft_strncmp(s, "EA", 2) && (s[2] == ' ' || s[2] == '\t' || !s[2]))
		return (4);
	if (s[0] == 'F' && (s[1] == ' ' || s[1] == '\t' || !s[1]))
		return (5);
	if (s[0] == 'C' && (s[1] == ' ' || s[1] == '\t' || !s[1]))
		return (6);
	return (0);
}

/* check texture + colors set */
static int	all_elements_set(t_data *data)
{
	return (data->cfg.no && data->cfg.so && data->cfg.we && data->cfg.ea
		&& data->cfg.floor != -1 && data->cfg.ceiling != -1);
}

/* parse lines (NO/SO/WE/EA/F/C) */
int	process_lines(t_data *data, char **lines)
{
	int		i;
	char	*t;

	i = 0;
	while (lines[i])
	{
		t = skip_spaces(lines[i]);
		if (line_is_empty(t))
			i++;
		else if (get_element_id(t) == 0)
			break ;
		else
		{
			parse_element(data, t);
			i++;
		}
	}
	if (!all_elements_set(data))
		error_exit(data, "Missing or duplicate element (NO SO WE EA F C)");
	if (!lines[i])
		error_exit(data, "Empty map");
	build_map(data, lines, i);
	return (1);
}
