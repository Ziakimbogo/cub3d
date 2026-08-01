/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catrenet <catrenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 16:42:57 by gechavia          #+#    #+#             */
/*   Updated: 2026/07/28 11:28:22 by catrenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	strip_newline(char *s)
{
	int	len;

	len = ft_strlen(s);
	if (len > 0 && s[len - 1] == '\n')
		s[--len] = '\0';
	if (len > 0 && s[len - 1] == '\r')
		s[--len] = '\0';
}

static char	**append_line(char **arr, char *s, int n)
{
	char	**new;
	int		i;

	new = (char **)malloc(sizeof(char *) * (n + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (i < n)
	{
		new[i] = arr[i];
		i++;
	}
	new[n] = s;
	new[n + 1] = NULL;
	free(arr);
	return (new);
}

char	**read_file_lines(int fd)
{
	char	**lines;
	char	*line;
	int		n;

	lines = (char **)malloc(sizeof(char *));
	if (!lines)
		return (NULL);
	lines[0] = NULL;
	n = 0;
	line = get_next_line(fd);
	while (line)
	{
		strip_newline(line);
		lines = append_line(lines, line, n++);
		if (!lines)
			return (NULL);
		line = get_next_line(fd);
	}
	return (lines);
}

int	parse_map(char *file, t_data *data)
{
	int		fd;
	char	**lines;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nCannot open map file\n", 2);
		return (0);
	}
	lines = read_file_lines(fd);
	close(fd);
	if (!lines)
		error_exit(data, "Malloc failed");
	data->tmp.lines = lines;
	process_lines(data, lines);
	data->tmp.lines = NULL;
	free_lines(lines);
	return (1);
}
