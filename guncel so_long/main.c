/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdinc <mdinc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 23:26:29 by mdinc             #+#    #+#             */
/*   Updated: 2025/03/05 23:27:13 by mdinc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include "so_long.h"

#define WIDTH 800
#define HEIGHT 600
#define TILE_SIZE 64  // Her bir karenin boyutu

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
        free_map(data->map);
    if (data->win)
        mlx_destroy_window(data->mlx, data->win);
    if (data->mlx)
    {
        mlx_destroy_display(data->mlx);// sadece görsel ile ilgili kaynakları freeler
        free(data->mlx);//mlx bağlamını tamamen serbest bırakılır
    }
    free(data);
    return (1);
}

void find_player_pos(t_data *data, int *x, int *y)
{
    *y = 0;
    while (data->map[*y])
    {
        *x = 0;
        while (data->map[*y][*x])
        {
            if (data->map[*y][*x] == 'P')
                return;
            (*x)++;
        }
        (*y)++;
    }
}

static int g_move_count = 0;

void increment_move_counter(void)
{
    g_move_count++;
    printf("%d\n", g_move_count);
}

int handle_collectible(t_data *data, int x, int y)
{
    if (data->map[y][x] == 'C')
    {
        data->collectibles--;
        printf("Kalan collectible: %d\n", data->collectibles);
        return (1);
    }
    return (0);
}

int handle_exit(t_data *data, int x, int y)
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
        printf("Önce tüm collectible'ları toplamalısın! Kalan: %d\n", data->collectibles);
        return (1);
    }
    return (0);
}

int is_valid_move(t_data *data, int new_x, int new_y)
{
    return (new_x >= 0 && new_x < get_map_width(data->map) && 
            new_y >= 0 && new_y < get_map_height(data->map) && 
            data->map[new_y][new_x] != '1');
}

void perform_movement(t_data *data, int old_x, int old_y, int new_x, int new_y)
{
    data->map[old_y][old_x] = '0';
    data->map[new_y][new_x] = 'P';
    draw_map(data);
    increment_move_counter();
}

void move_player(t_data *data, int new_x, int new_y)
{
    int current_x, current_y;

    find_player_pos(data, &current_x, &current_y);

    if (!is_valid_move(data, new_x, new_y))
        return;

    if (handle_collectible(data, new_x, new_y))
    {
        perform_movement(data, current_x, current_y, new_x, new_y);
        return;
    }

    if (handle_exit(data, new_x, new_y))
        return;

    perform_movement(data, current_x, current_y, new_x, new_y);
}

int key_press(int keycode, t_data *data)
{
    int x, y;

    find_player_pos(data, &x, &y);

    if (keycode == 65307) // ESC tuşu
    {
        mlx_loop_end(data->mlx);
        return (1);
    }
    else if (keycode == 119) // W tuşu - yukarı
        move_player(data, x, y - 1);
    else if (keycode == 115) // S tuşu - aşağı
        move_player(data, x, y + 1);
    else if (keycode == 97)  // A tuşu - sol
        move_player(data, x - 1, y);
    else if (keycode == 100) // D tuşu - sağ
        move_player(data, x + 1, y);

    return (0);
}

void draw_map(t_data *data)
{
    int y = 0;
    int x;
    
    while (data->map[y])
    {
        x = 0;
        while (data->map[y][x])
        {
			// (x,y) kordinatları son iki parametre x arttıkça sağa y arttıkça aşşağı gider orijin sol üst olur.
            if (data->map[y][x] == '1')
                mlx_put_image_to_window(data->mlx, data->win, data->wall, x * TILE_SIZE, y * TILE_SIZE);
            else if (data->map[y][x] == '0')
                mlx_put_image_to_window(data->mlx, data->win, data->floor, x * TILE_SIZE, y * TILE_SIZE);
            else if (data->map[y][x] == 'P')
                mlx_put_image_to_window(data->mlx, data->win, data->player, x * TILE_SIZE, y * TILE_SIZE);
            else if (data->map[y][x] == 'C')
                mlx_put_image_to_window(data->mlx, data->win, data->collect, x * TILE_SIZE, y * TILE_SIZE);
            else if (data->map[y][x] == 'E')
                mlx_put_image_to_window(data->mlx, data->win, data->exit, x * TILE_SIZE, y * TILE_SIZE);
            x++;
        }
        y++;
    }
}

int get_map_width(char **map)
{
    int width = 0;
    while (map[0][width])
        width++;
    return width;
}

int get_map_height(char **map)
{
    int height = 0;
    while (map[height])
        height++;
    return height;
}

t_data *init_data(void)
{
    t_data *data = malloc(sizeof(t_data));
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

int load_textures(t_data *data)
{
    int img_width;
    int img_height;

    data->wall = mlx_xpm_file_to_image(data->mlx, "textures/wall.xpm", &img_width, &img_height);
    data->floor = mlx_xpm_file_to_image(data->mlx, "textures/floor.xpm", &img_width, &img_height);
    data->player = mlx_xpm_file_to_image(data->mlx, "textures/player.xpm", &img_width, &img_height);
    data->collect = mlx_xpm_file_to_image(data->mlx, "textures/collect.xpm", &img_width, &img_height);
    data->exit = mlx_xpm_file_to_image(data->mlx, "textures/exit.xpm", &img_width, &img_height);

    if (!data->wall || !data->floor || !data->player || !data->collect || !data->exit)
        return (0);
    return (1);
}

int setup_window(t_data *data)
{
    int map_width = get_map_width(data->map);
    int map_height = get_map_height(data->map);
    
    data->win = mlx_new_window(data->mlx, map_width * TILE_SIZE, map_height * TILE_SIZE, "So Long");
    if (!data->win)
        return (0);
    return (1);
}

int count_collectibles(t_data *data)
{
    int count = 0;
    int y = 0;
    
    while (data->map[y])
    {
        int x = 0;
        while (data->map[y][x])
        {
            if (data->map[y][x] == 'C')
                count++;
            x++;
        }
        y++;
    }
    return (count);
}

int setup_map(t_data *data, char *map_path)
{
    data->map = read_map(map_path);
    if (!data->map)
        return (0);

    check_valid_chars(data, get_map_height(data->map), get_map_width(data->map));

    if (!check_collectibles(data->map, get_map_width(data->map), get_map_height(data->map)))
        return (0);

    data->collectibles = count_collectibles(data);
    return (1);
}

int handle_window_close(t_data *data)
{
    mlx_loop_end(data->mlx);
    return (0);
}

int main(int argc, char *argv[])
{
    t_data *data;
    int return_value = 0;

    if (argc != 2)
    {
        printf("Error\nUsage: %s <map.ber>\n", argv[0]);
        return (1);
    }

    data = init_data();
    if (!data)
        return (1);

    if (!setup_map(data, argv[1]) || !load_textures(data) || !setup_window(data))
    {
        close_window(data);
        return (1);
    }

    draw_map(data);

    mlx_hook(data->win, 17, 0, handle_window_close, data);  // Changed this line
    mlx_hook(data->win, 2, 1L << 0, key_press, data);

    mlx_loop(data->mlx);
    return_value = close_window(data);

    return (return_value);
}

/*Nasıl oluyorda key_press e tek parametre girmemize rağmen 2 tane alıyor?
Burada bir olay gerçekleştiğinde, MLX kütüphanesi otomatik olarak uygun parametreleri fonksiyona gönderir. 
Sen sadece hangi fonksiyonun çağrılacağını ve ekstra bir parametre (param) belirtiyorsun.*/
