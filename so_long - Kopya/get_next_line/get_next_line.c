/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdinc <mdinc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 16:25:00 by mdinc             #+#    #+#             */
/*   Updated: 2024/12/21 17:22:34 by mdinc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

static char	*ft_new_rest(char *rest)
{
	char	*new_line;
	int		i;
	int		j;

	i = ft_count_newline(rest);
	if (!rest[i] && rest)
	{
		free(rest);
		return (NULL);
	}
	new_line = malloc(ft_strlen(rest) - i + 1);
	if (!new_line)
	{
		free(rest);
		return (NULL);
	}
	i++;
	j = 0;
	while (rest[i])
		new_line[j++] = rest[i++];
	new_line[j] = '\0';
	free(rest);
	return (new_line);
}

static char	*ft_red_line(char *rest)
{
	char	*line;
	int		j;

	j = 0;
	if (!rest[j])
		return (NULL);
	if (ft_strchr(rest, '\n'))
		line = malloc(ft_count_newline(rest) + 2);
	else
		line = malloc(ft_count_newline(rest) + 1);
	if (!line)
		return (free(rest), NULL);
	j = -1;
	while (rest[++j] != '\n' && rest[j] != '\0')
		line[j] = rest[j];
	if (rest[j] == '\n')
	{
		line[j] = rest[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*ft_get_rest(int fd, char *rest)
{
	int		read_byte;
	char	*temp;

	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
	{
		free(rest);
		return (NULL);
	}
	read_byte = 1;
	while (read_byte != 0 && !ft_where_newline(rest))
	{
		read_byte = read(fd, temp, BUFFER_SIZE);
		if (read_byte == -1)
		{
			free(rest);
			free(temp);
			return (NULL);
		}
		temp[read_byte] = '\0';
		rest = ft_strjoin(rest, temp);
	}
	free(temp);
	return (rest);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*rest;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(rest);
		return (NULL);
	}
	rest = ft_get_rest(fd, rest);
	if (!rest)
		return (NULL);
	line = ft_red_line(rest);
	rest = ft_new_rest(rest);
	return (line);
}
