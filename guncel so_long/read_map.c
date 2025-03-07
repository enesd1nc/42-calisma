#include "get_next_line/get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h> 
#include "so_long.h" // close fonksiyonu için gerekli
#include <stdio.h>

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

int count_lines(char *filename)
{
	int fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	char *line;
	int count = 0;
	while ((line = get_next_line(fd)))
	{
		count++;
		free(line);
	}
	close(fd);
	return (count);
}

int get_line_len(char *line)
{
    int len = 0;
    while (line[len] && line[len] != '\n' && line[len] != '\r')
        len++;
    return len;
}

void    init_map_info(t_map_info *info, char *map)
{
    info->red = 1;
    info->counter1 = 0;
    info->counter2 = 0;
    info->counter3 = 0;
    info->j = 0;
    info->line_count = count_lines(map);
    info->first_line_len = 0;
    info->line = NULL;
    info->rest = NULL;
    info->fd = -1;
}

static int check_map_validity(t_map_info info, char **map)
{
    if (info.j != info.line_count || info.counter1 != 1 || info.counter2 != 1 || 
        info.counter3 < 1 || info.red < 0)
    {
        free_map(map);
        close(info.fd);
        return (0);
    }
    return (1);
}

static void count_map_chars(char c, t_map_info *info)
{
    if (c == 'E')
        info->counter1++;
    if (c == 'P')
        info->counter2++;
    if (c == 'C')
        info->counter3++;
}

static char **allocate_map(int line_count)
{
    char **map = (char **)calloc((line_count + 1), sizeof(char *));
    if (!map)
        return (NULL);
    return map;
}

static char *allocate_line(int line_len)
{
    char *line = (char *)calloc(line_len + 1, sizeof(char));
    return line;
}

static int initialize_map_reading(t_map_info *info, char *map)
{
    init_map_info(info, map);
    if (info->line_count <= 0)
        return (0);

    info->fd = open(map, O_RDONLY);
    if (info->fd < 0)
        return (0);
    
    info->rest = allocate_map(info->line_count);
    if (!info->rest)
    {
        close(info->fd);
        return (0);
    }

    info->line = get_next_line(info->fd);
    if (!info->line)
    {
        free(info->rest);
        close(info->fd);
        return (0);
    }
    
    info->first_line_len = get_line_len(info->line);
    return (1);
}

static int handle_line_allocation_error(char *line_ptr, char *line, int fd)
{
    if (!line_ptr)
    {
        free(line);
        close(fd);
        return (1);
    }
    return (0);
}

static void process_line_cleanup(t_map_info *info, int k)
{
    info->rest[info->j][k] = '\0';
    free(info->line);
    info->line = get_next_line(info->fd);
    info->j++;
}

static void process_line(t_map_info *info, int k)
{
    while (k < info->first_line_len)
    {
        if ((info->j == 0 || info->j == info->line_count - 1) && info->line[k] != '1')
        {
            info->red = -1;
            break;
        }

        if ((k == 0 || k == info->first_line_len - 1) && info->line[k] != '1')
        {
            info->red = -1;
            break;
        }

        info->rest[info->j][k] = info->line[k];
        count_map_chars(info->line[k], info);
        k++;
    }
    process_line_cleanup(info, k);
}

char **read_map(char *map)
{
    t_map_info info;

    if (!initialize_map_reading(&info, map))
        return (NULL);

    while (info.line && info.j < info.line_count)
    {
        int current_len = get_line_len(info.line);
        if (current_len != info.first_line_len)
            info.red = -1;
        info.rest[info.j] = allocate_line(info.first_line_len);
        if (handle_line_allocation_error(info.rest[info.j], info.line, info.fd))
        {
            free_map(info.rest);
            return (NULL);
        }
        process_line(&info, 0);
    }
    info.rest[info.j] = NULL;
    if (!check_map_validity(info, info.rest))
        return (NULL);

    close(info.fd);
    return (info.rest);
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