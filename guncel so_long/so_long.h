/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdinc <mdinc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:31:35 by mdinc             #+#    #+#             */
/*   Updated: 2025/03/08 16:31:37 by mdinc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "get_next_line/get_next_line.h"
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*wall;
	void	*floor;
	void	*player;
	void	*collect;
	void	*exit;
	char	**map;
	int		collectibles;
}			t_data;

typedef struct s_movement
{
	int		old_x;
	int		old_y;
	int		new_x;
	int		new_y;
}			t_movement;

typedef struct s_map_info
{
	int		fd;
	char	*line;
	char	**rest;
	int		j;
	int		red;
	int		counter1;
	int		counter2;
	int		counter3;
	int		line_count;
	int		first_line_len;
}			t_map_info;

typedef struct s_pos
{
	int		x;
	int		y;
}			t_pos;

typedef struct s_flood
{
	char	**map;
	int		x;
	int		y;
	int		*visited;
	int		width;
	int		height;
	int		check_collectibles;
}			t_flood;

typedef struct s_map_row
{
	char	*row;
	int		y;
	int		width;
	t_pos	*player;
	int		*exit_found;
}			t_map_row;

typedef struct s_check_info
{
	char	**map;
	int		*visited;
	int		*visited_exit;
	int		width;
	int		height;
}			t_check_info;

char		**read_map(char *map);
void		free_map(char **map);
int			close_window(t_data *data);
void		draw_map(t_data *data);
void		draw_map_row(t_data *data, int y);
int			key_press(int keycode, t_data *data);
void		find_player_pos(t_data *data, int *x, int *y);
void		move_player(t_data *data, int new_x, int new_y);
int			check_collectibles(char **map, int width, int height);
void		check_valid_chars(t_data *data, int height, int width);
int			get_map_width(char **map);
int			get_map_height(char **map);
int			init_game(t_data **data, char *map_path);
void		setup_game_hooks(t_data *data);
void		init_map_info(t_map_info *info, char *map);

#endif