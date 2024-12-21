/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdinc <mdinc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:58:33 by mdinc             #+#    #+#             */
/*   Updated: 2024/12/21 20:58:36 by mdinc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>

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
	while (remainder[i])//(str[i] != '\0') ile aynı
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
	read_len = 1;
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
	static char	*remainder;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remainder = ft_get_remainder(fd, remainder);
	if (!remainder)
		return (NULL);
	line = ft_get_line(remainder);
	remainder = ft_get_new_remainder(remainder);
	return (line);
}
#include <stdio.h>
int main()
{
	char	*line;
	int		fd = open("text2.txt", O_RDONLY);
	
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		printf("%s",line);
		free(line);
	}
}
/*Dosya Konumu (File Offset)
read fonksiyonu, dosya tanımlayıcısının dosya konumu bilgisini kullanarak, bir sonraki okumanın nereden başlaması gerektiğini bilir.
İlk read çağrısından sonra, dosya konumu otomatik olarak okunan bayt sayısı kadar ileri taşınır.
Böylece, sonraki read çağrısı önceki okumanın bittiği yerden başlar.
read fonksiyonu '\n' ve '\0' da sayar
bu kodlar ile derle cc -Wall -Wextra -Werror -D BUFFER_SIZE=10 get_next_line.c get_next_line_utils.o
-D makro tanımlamak için kullanılır define gibi*/