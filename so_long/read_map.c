#include "get_next_line/get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>

int	str_len(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**read_map(char *map)
{
	int		fd;
	char	*line;
	char	**rest;
	int		j = 0;

	fd = open(map, O_RDONLY);
	rest =(char **)malloc(sizeof(char *) * 6);
	while ((line = get_next_line(fd)))
	{
		rest[j] = malloc(sizeof(char) * str_len(line) + 1);
		int k = 0;
		while(*line)
		{
			rest[j][k++] = *line++;
		}
		rest[j][k] = '\0';
		j++;
	}
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