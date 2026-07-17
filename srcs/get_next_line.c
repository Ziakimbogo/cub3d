/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gechavia <chaviallegeraud@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:21:14 by gechavia          #+#    #+#             */
/*   Updated: 2025/06/12 01:54:17 by gechavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_free_reserve(char **reserve)
{
	if (*reserve)
	{
		free(*reserve);
		*reserve = NULL;
	}
}

static char	*ft_update_reserve(char *reserve)
{
	int		i;
	int		len;
	char	*new_res;
	int		j;

	if (!reserve)
		return (NULL);
	i = 0;
	while (reserve[i] && reserve[i] != '\n')
		i++;
	if (!reserve[i] || !reserve[i + 1])
		return (free(reserve), NULL);
	len = ft_strlen(reserve + i + 1);
	new_res = malloc(sizeof(char) * (len + 1));
	if (!new_res)
		return (free(reserve), NULL);
	j = -1;
	while (++j < len)
		new_res[j] = reserve[i + 1 + j];
	new_res[j] = '\0';
	return (free(reserve), new_res);
}

static int	ft_read_and_join(int fd, char **reserve, char *buffer)
{
	int		bytes_read;
	char	*temp;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read == -1)
		return (ft_free_reserve(reserve), -1);
	buffer[bytes_read] = '\0';
	temp = ft_strjoin(*reserve, buffer);
	if (!temp)
		return (ft_free_reserve(reserve), -1);
	if (*reserve)
		free(*reserve);
	*reserve = temp;
	return (bytes_read);
}

static char	*ft_handle_end(char **reserve)
{
	char	*line;

	if (!*reserve || !**reserve)
		return (ft_free_reserve(reserve), NULL);
	line = ft_extract_line(*reserve);
	if (!line)
		return (ft_free_reserve(reserve), NULL);
	*reserve = ft_update_reserve(*reserve);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*reserve;
	char		*buffer;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_free_reserve(&reserve), NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free_reserve(&reserve), NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(reserve, '\n'))
	{
		bytes_read = ft_read_and_join(fd, &reserve, buffer);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	return (ft_handle_end(&reserve));
}
