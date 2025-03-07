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

#include "so_long.h"
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

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
		while (data->map[*y][*x])
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

void	perform_movement(t_data *data, t_movement move)
{
	data->map[move.old_y][move.old_x] = '0';
	data->map[move.new_y][move.new_x] = 'P';
	draw_map(data);
	increment_move_counter();
}

void	move_player(t_data *data, int new_x, int new_y)
{
	t_movement	move;
	int			current_x;
	int			current_y;

	find_player_pos(data, &current_x, &current_y);
	if (!is_valid_move(data, new_x, new_y))
		return ;
	move.old_x = current_x;
	move.old_y = current_y;
	move.new_x = new_x;
	move.new_y = new_y;
	if (handle_collectible(data, new_x, new_y))
	{
		perform_movement(data, move);
		return ;
	}
	if (handle_exit(data, new_x, new_y))
		return ;
	perform_movement(data, move);
}

int	key_press(int keycode, t_data *data)
{
	int	x;
	int	y;

	find_player_pos(data, &x, &y);
	if (keycode == 65307)
	{
		mlx_loop_end(data->mlx);
		return (1);
	}
	else if (keycode == 119)
		move_player(data, x, y - 1);
	else if (keycode == 115)
		move_player(data, x, y + 1);
	else if (keycode == 97)
		move_player(data, x - 1, y);
	else if (keycode == 100)
		move_player(data, x + 1, y);
	return (0);
}

void	draw_map_row(t_data *data, int y)
{
	int	x;

	x = 0;
	while (data->map[y][x])
	{
		if (data->map[y][x] == '1')
			mlx_put_image_to_window(data->mlx, data->win, data->wall, x
				* TILE_SIZE, y * TILE_SIZE);
		else if (data->map[y][x] == '0')
			mlx_put_image_to_window(data->mlx, data->win, data->floor, x
				* TILE_SIZE, y * TILE_SIZE);
		else if (data->map[y][x] == 'P')
			mlx_put_image_to_window(data->mlx, data->win, data->player, x
				* TILE_SIZE, y * TILE_SIZE);
		else if (data->map[y][x] == 'C')
			mlx_put_image_to_window(data->mlx, data->win, data->collect, x
				* TILE_SIZE, y * TILE_SIZE);
		else if (data->map[y][x] == 'E')
			mlx_put_image_to_window(data->mlx, data->win, data->exit, x
				* TILE_SIZE, y * TILE_SIZE);
		x++;
	}
}

void	draw_map(t_data *data)
{
	int	y;

	y = 0;
	while (data->map[y])
	{
		draw_map_row(data, y);
		y++;
	}
}

int	get_map_width(char **map)
{
	int	width;

	width = 0;
	while (map[0][width])
		width++;
	return (width);
}

int	get_map_height(char **map)
{
	int	height;

	height = 0;
	while (map[height])
		height++;
	return (height);
}

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	memset(data, 0, sizeof(t_data));
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		free(data);
		return (NULL);
	}
	return (data);
}

int	load_textures(t_data *data)
{
	int		img_width;
	int		img_height;

	data->wall = mlx_xpm_file_to_image(data->mlx, "textures/wall.xpm",
			&img_width, &img_height);
	data->floor = mlx_xpm_file_to_image(data->mlx, "textures/floor.xpm",
			&img_width, &img_height);
	data->player = mlx_xpm_file_to_image(data->mlx, "textures/player.xpm",
			&img_width, &img_height);
	data->collect = mlx_xpm_file_to_image(data->mlx, "textures/collect.xpm",
			&img_width, &img_height);
	data->exit = mlx_xpm_file_to_image(data->mlx, "textures/exit.xpm",
			&img_width, &img_height);
	if (!data->wall || !data->floor || !data->player || !data->collect
		|| !data->exit)
		return (0);
	return (1);
}
