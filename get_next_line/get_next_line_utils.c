/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdinc <mdinc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:58:25 by mdinc             #+#    #+#             */
/*   Updated: 2024/12/24 17:04:28 by mdinc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	ft_count_newline(char *remainder)
{
	int	i;

	i = 0;
	if (!remainder)
		return (0);
	while (remainder[i] != '\n' && remainder[i])
		i++;
	return (i);
}

char	*ft_check_newline(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '\n')
			return (s + i);
		i++;
	}
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*join;

	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	join = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!join)
		return (free(s1), NULL);
	i = -1;
	while (s1[++i] != '\0')
		join[i] = s1[i];
	j = 0;
	while (s2[j] != '\0')
		join[i++] = s2[j++];
	join[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	free(s1);
	return (join);
}

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	tmp;

	i = 0;
	tmp = (unsigned char)c;
	while (s[i])
	{
		if (s[i] == tmp)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	return (NULL);
}
