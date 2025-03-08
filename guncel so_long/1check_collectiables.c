/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1check_collectiables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdinc <mdinc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:57:54 by mdinc             #+#    #+#             */
/*   Updated: 2025/03/08 15:49:18 by mdinc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>
#include <stdlib.h>

void	flood_fill(t_flood *flood)
{
	t_flood	next;

	if (flood->x < 0 || flood->x >= flood->width || flood->y < 0
		|| flood->y >= flood->height || !flood->map || !flood->map[flood->y])
		return ;
	if (flood->map[flood->y][flood->x] == '1' || flood->visited[flood->y
		* flood->width + flood->x])
		return ;
	if (flood->check_collectibles && flood->map[flood->y][flood->x] == 'E')
		return ;
	flood->visited[flood->y * flood->width + flood->x] = 1;
	next = *flood;
	next.x = flood->x + 1;
	flood_fill(&next);
	next.x = flood->x - 1;
	flood_fill(&next);
	next.x = flood->x;
	next.y = flood->y + 1;
	flood_fill(&next);
	next.y = flood->y - 1;
	flood_fill(&next);
}

static void	check_cell_for_player(char cell, int x, int y, t_pos *player)
{
	if (cell == 'P')
	{
		player->x = x;
		player->y = y;
	}
}

static void	check_cell_for_exit(char cell, int *exit_found)
{
	if (cell == 'E')
		*exit_found = 1;
}

static void	process_map_row(t_map_row *row_info)
{
	int	j;

	j = 0;
	while (j < row_info->width)
	{
		check_cell_for_player(row_info->row[j], j, row_info->y,
			row_info->player);
		check_cell_for_exit(row_info->row[j], row_info->exit_found);
		j++;
	}
}

static t_pos	find_player(char **map, int width, int height, int *exit_found)
{
	t_pos		player;
	int			i;
	t_map_row	row_info;

	player = (t_pos){-1, -1};
	i = 0;
	while (i < height)
	{
		if (!map[i])
		{
			i++;
			continue ;
		}
		row_info.row = map[i];
		row_info.y = i;
		row_info.width = width;
		row_info.player = &player;
		row_info.exit_found = exit_found;
		process_map_row(&row_info);
		i++;
	}
	return (player);
}

static int	check_map_validity(t_pos player, int exit_found)
{
	if (player.x == -1)
	{
		printf("Hata: Oyuncu (P) bulunamadı!\n");
		return (0);
	}
	if (!exit_found)
	{
		printf("Hata: Çıkış (E) bulunamadı!\n");
		return (0);
	}
	return (1);
}

static int	check_collectible_access(char cell, int visited_status)
{
	if (cell == 'C' && !visited_status)
	{
		printf("Hata: Oyuncu tüm toplanabilir nesnelere ulaşamıyor!\n");
		return (0);
	}
	return (1);
}

static int	check_exit_access(char cell, int visited_status)
{
	if (cell == 'E' && !visited_status)
	{
		printf("Hata: Oyuncu çıkışa ulaşamıyor!\n");
		return (0);
	}
	return (1);
}

static int	check_cell(char cell, int *visited, int *visited_exit, int index)
{
	if (!check_collectible_access(cell, visited[index]))
		return (0);
	if (!check_exit_access(cell, visited_exit[index]))
		return (0);
	return (1);
}

static int	perform_checks(t_check_info *check)
{
	int	i;
	int	j;

	i = 0;
	while (i < check->height)
	{
		if (!check->map[i])
		{
			i++;
			continue ;
		}
		j = 0;
		while (j < check->width)
		{
			if (!check_cell(check->map[i][j], check->visited,
				check->visited_exit, i * check->width + j))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	init_visited_arrays(int **visited, int **visited_exit, int width,
		int height)
{
	*visited = calloc(width * height, sizeof(int));
	*visited_exit = calloc(width * height, sizeof(int));
	if (!(*visited) || !(*visited_exit))
	{
		free(*visited);
		free(*visited_exit);
		*visited = NULL;
		*visited_exit = NULL;
		return (0);
	}
	return (1);
}

static void	perform_flood_fills(t_flood *flood, int *visited_exit)
{
	flood_fill(flood);
	flood->visited = visited_exit;
	flood->check_collectibles = 0;
	flood_fill(flood);
}

static void	cleanup_arrays(int *visited, int *visited_exit)
{
	free(visited);
	free(visited_exit);
}

static int	handle_flood_and_checks(t_flood *flood, char **map, int *visited,
		int *visited_exit)
{
	t_check_info	check;
	int				result;

	perform_flood_fills(flood, visited_exit);
	check.map = map;
	check.visited = visited;
	check.visited_exit = visited_exit;
	check.width = flood->width;
	check.height = flood->height;
	result = perform_checks(&check);
	cleanup_arrays(visited, visited_exit);
	return (result);
}

int	check_collectibles(char **map, int width, int height)
{
	int		*visited;
	int		*visited_exit;
	int		exit_found;
	t_pos	player;
	t_flood	flood;

	if (!map || width <= 0 || height <= 0)
		return (0);
	visited = NULL;
	visited_exit = NULL;
	exit_found = 0;
	if (!init_visited_arrays(&visited, &visited_exit, width, height))
		return (0);
	player = find_player(map, width, height, &exit_found);
	if (!check_map_validity(player, exit_found))
	{
		cleanup_arrays(visited, visited_exit);
		return (0);
	}
	flood = (t_flood){.map = map, .x = player.x, .y = player.y,
		.visited = visited, .width = width, .height = height,
		.check_collectibles = 1};
	return (handle_flood_and_checks(&flood, map, visited, visited_exit));
}
