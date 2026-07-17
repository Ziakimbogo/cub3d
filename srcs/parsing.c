/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gechavia <gechavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 16:42:57 by gechavia          #+#    #+#             */
/*   Updated: 2026/07/17 04:54:53 by gechavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Enlève les char de fin de ligne (\n puis \r pour les
   CR = \r = windows et LF = \n = unix le tout formant le CRLF*/
void	strip_newline(char *s)
{
	int	len;

	len = ft_strlen(s);
	if (len > 0 && s[len - 1] == '\n')
		s[--len] = '\0';
	if (len > 0 && s[len - 1] == '\r')
		s[--len] = '\0';
}

/* Duplication d'un tableau de lignes + ajout d'une ligne à la fin.
   Libère l'ancien tableau. */
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

/* lit tableau ligne par ligne */
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

/* ouvre le fichier, lit les lignes, sépare
   éléments et map, construit la grille */
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
	process_lines(data, lines);
	free_lines(lines);
	return (1);
}
