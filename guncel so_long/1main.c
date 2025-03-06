/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdinc <mdinc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:21:44 by mdinc             #+#    #+#             */
/*   Updated: 2025/03/06 22:21:44 by mdinc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "so_long.h"
#include <mlx.h>

#define TILE_SIZE 64

int	close_window(t_data *data)
{
	if (!data)
		return (0);
	if (data->wall)
		mlx_destroy_image(data->mlx, data->wall);
	if (data->floor)
		mlx_destroy_image(data->mlx, data->floor);
	if (data->player)
		mlx_destroy_image(data->mlx, data->player);
	if (data->collect)
		mlx_destroy_image(data->mlx, data->collect);
	if (data->exit)
		mlx_destroy_image(data->mlx, data->exit);
	if (data->map)
		mlx_destroy_image(data->mlx, data->map);
	if (data->win)
		mlx_destroy_image(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	free(data);
	return (1);
}

void	find_player_pos(t_data *data, int *x, int *y)
{
	*y = 0;
	while (data->map[*y])
	{
		*x = 0;
		while (data-> map[*y][*x])
		{
			if (data->map[*y][*x] == 'P')
				return ;
			(*x)++;
		}
		(*y++);
	}
}

static int	g_move_count = 0;

void	increment_move_counter(void)
{
	g_move_count++;
	printf("%d\n", g_move_count);
}

int	handle_collectible(t_data *data, int x, int y)
{
	if (data->map[y][x] == 'C')
	{
		data->collectibles--;
		printf("Kalan collectible: %d\n,", data->collectibles);
		return (1);
	}
	return (0);
}

int	handle_exit(t_data *data, int x, int y)
{
	if (data->map[y][x] == 'E')
	{
		if (data->collectibles == 0)
		{
			increment_move_counter();
			printf("%s\n", "Tüm collectible'lar toplandı, oyun bitti!");
			mlx_loop_end(data->mlx);
			return (1);
		}
		printf("Önce tüm collectible'ları toplamalısın!");
		printf("Kalan: %d\n", data->collectibles);
		return (1);
	}
	return (0);
}
//dikkat
int	is_valid_move(t_data *data, int new_x, int new_y)
{
	if (new_x < 0 || new_x >= get_map_width(data->map))
		return (0);
	if (new_y < 0 || new_y >= get_map_height(data->map))
		return (0);
	if (data->map[new_y][new_x] == '1')
		return (0);
	return (1);
}

void	perform_movement(t_data *data, int old_x, int old_y, int new_x, int new_y)
{
	
}