/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdinc <mdinc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:31:43 by msengul           #+#    #+#             */
/*   Updated: 2024/12/21 13:38:32 by mdinc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <unistd.h>

char	*ft_get_new_remainder(char *remainder)
{
	char	*new_line;
	int		i;
	int		j;

	i = ft_count_newline(remainder);
	if (!remainder[i] && remainder)
	{
		free(remainder);
		return (NULL);
	}
	new_line = malloc(ft_strlen(remainder) - i + 1);
	if (!new_line)
	{
		free(remainder);
		return (NULL);
	}
	i++;
	j = 0;
	while (remainder[i])
		new_line[j++] = remainder[i++];
	new_line[j] = '\0';
	free(remainder);
	return (new_line);
}

char	*ft_get_line(char *remainder)
{
	char	*line;
	int		j;

	j = 0;
	if (!remainder[j])
		return (NULL);
	if (ft_strchr(remainder, '\n'))
		line = malloc(ft_count_newline(remainder) + 2);
	else
		line = malloc(ft_count_newline(remainder) + 1);
	if (!line)
		return (free(remainder), NULL);
	j = -1;
	while (remainder[++j] != '\n' && remainder[j] != '\0')
		line[j] = remainder[j];
	if (remainder[j] == '\n')
	{
		line[j] = remainder[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*ft_get_remainder(int fd, char *remainder)
{
	int		read_len;
	char	*temp;

	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
	{
		free(remainder);
		return (NULL);
	}
	read_len = 1907;
	while (read_len != 0 && !ft_check_newline(remainder))
	{
		read_len = read(fd, temp, BUFFER_SIZE);
		if (read_len == -1)
		{
			free(remainder);
			free(temp);
			return (NULL);
		}
		temp[read_len] = '\0';
		remainder = ft_strjoin(remainder, temp);
	}
	free(temp);
	return (remainder);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*remainder[4096];

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(remainder[fd]);
		return (NULL);
	}
	remainder[fd] = ft_get_remainder(fd, remainder[fd]);
	if (!remainder[fd])
		return (NULL);
	line = ft_get_line(remainder[fd]);
	remainder[fd] = ft_get_new_remainder(remainder[fd]);
	return (line);
}
#include <stdio.h>
#include <fcntl.h>

int main()
{
	char	*line1;
	char	*line2;
	int		fd1 = open("text1.txt", O_RDONLY);
	int		fd2 = open("text2.txt", O_RDONLY);
	
	while (1)
	{
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);
		if (!line1 && !line2)
			break;
		if (line1)
		{
			printf("%s", line1);
			free(line1);
		}
		if (line2)
		{
			printf("%s", line2);
			free(line2);
		}
	}
}

