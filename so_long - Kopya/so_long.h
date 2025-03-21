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
}   t_data;

// Fonksiyon prototipleri
char    **read_map(char *map);
void    free_map(char **map);
int     close_window(t_data *data);
void    draw_map(t_data *data);
int     key_press(int keycode, t_data *data);
void    find_player_pos(t_data *data, int *x, int *y);
void    move_player(t_data *data, int new_x, int new_y);

// Yardımcı fonksiyonlar
void    *ft_memset(void *b, int c, size_t len);

#endif