#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "get_next_line/get_next_line.h"

typedef struct s_data
{
    void    *mlx;
    void    *win;
    void    *wall;
    void    *floor;
    void    *player;
    void    *collect;
    void    *exit;
    char    **map;
    int     collectibles;  // Toplanan collectible sayısı
}   t_data;

typedef struct s_movement {
    int old_x;
    int old_y;
    int new_x;
    int new_y;
} t_movement;

typedef struct s_map_info
{
    int     fd;
    char    *line;
    char    **rest;
    int     j;
    int     red;
    int     counter1;    // Exit counter
    int     counter2;    // Player counter
    int     counter3;    // Collectible counter
    int     line_count;  // Total lines in map
    int     first_line_len;  // Width of map
} t_map_info;

// Fonksiyon prototipleri
char    **read_map(char *map);
void    free_map(char **map);
int     close_window(t_data *data);
void    draw_map(t_data *data);
void    draw_map_row(t_data *data, int y);
int     key_press(int keycode, t_data *data);
void    find_player_pos(t_data *data, int *x, int *y);
void    move_player(t_data *data, int new_x, int new_y);
int     check_collectibles(char **map, int width, int height);  // Yeni eklenen fonksiyon prototipi
void    check_valid_chars(t_data *data, int height, int width);  // Add this line before #endif
int     get_map_width(char **map);
int     get_map_height(char **map);
int     init_game(t_data **data, char *map_path);
void    setup_game_hooks(t_data *data);
void    init_map_info(t_map_info *info, char *map);  // Add before #endif

#endif