/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gechavia <chaviallegeraud@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:21:10 by gechavia          #+#    #+#             */
/*   Updated: 2025/06/12 01:59:47 by gechavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *src)
{
	int		i;
	int		len;
	char	*str;

	len = ft_strlen(src);
	str = (char *)malloc(sizeof(*str) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (src[i])
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	cc;

	if (!s)
		return (NULL);
	cc = (unsigned char)c;
	while (*s && *s != cc)
		s++;
	if (*s == cc)
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		total;
	char	*final;
	int		i;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	total = ft_strlen(s1) + ft_strlen(s2);
	final = (char *)malloc(sizeof(char) * (total + 1));
	if (!final)
		return (NULL);
	while (*s1)
		final[i++] = *s1++;
	while (*s2)
		final[i++] = *s2++;
	final[i] = '\0';
	return (final);
}

char	*ft_extract_line(char *reserve)
{
	int		i;
	char	*line;

	if (!reserve || reserve[0] == '\0')
		return (NULL);
	i = 0;
	while (reserve[i] && reserve[i] != '\n')
		i++;
	if (reserve[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	line[i] = '\0';
	while (--i >= 0)
		line[i] = reserve[i];
	return (line);
}
