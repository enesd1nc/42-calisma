#include "get_next_line/get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>  // close fonksiyonu için gerekli

int	str_len(char *str)
{
	int i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

char	**read_map(char *map)
{
	int		fd;
	char	*line;
	char	**rest;
	int		j;

	j = 0;
	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (NULL);
	
	rest = (char **)malloc(sizeof(char *) * 7); // 6 satır + NULL için
	if (!rest)
		return (NULL);

	while ((line = get_next_line(fd)) && j < 6)
	{
		rest[j] = malloc(sizeof(char) * (str_len(line) + 1));
		if (!rest[j])
		{
			free_map(rest);
			free(line);
			close(fd);
			return (NULL);
		}

		int k = 0;
		while (line[k] && line[k] != '\n')
		{
			rest[j][k] = line[k];
			k++;
		}
		rest[j][k] = '\0';
		free(line);
		j++;
	}
	rest[j] = NULL;  // Diziyi NULL ile sonlandır
	close(fd);
	return (rest);
}
/*#include <stdio.h>
int main()
{
	char	**str;
	int j = 0;
	str = read_map("map.ber");
	while(j < 6)
	{
		printf("%s", str[j++]);
	}
	printf("\n");
}
*/