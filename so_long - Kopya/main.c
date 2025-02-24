#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include "so_long.h"

#define WIDTH 800
#define HEIGHT 600
#define TILE_SIZE 32  // Her bir karenin boyutu

int close_window(t_data *data)
{
    // Görüntüleri temizle
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
    
    // Haritayı temizle
    if (data->map)
        free_map(data->map);

    // Pencereyi temizle
    if (data->win)
        mlx_destroy_window(data->mlx, data->win);
    
    // MLX'i temizle
    if (data->mlx)
    {
        mlx_destroy_display(data->mlx);
        free(data->mlx);
    }
    exit(0);
    return (0);
}

int key_press(int keycode, t_data *data)
{
    if (keycode == 65307) // ESC tuşu
        close_window(data);
    else if (keycode == 119) // W tuşu
        printf("Yukarı hareket\n");
    else if (keycode == 115) // S tuşu
        printf("Aşağı hareket\n");
    else if (keycode == 97) // A tuşu
        printf("Sola hareket\n");
    else if (keycode == 100) // D tuşu
        printf("Sağa hareket\n");

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

int main()
{
    t_data data;
    int img_width;
    int img_height;

    // Struct'ı sıfırla
    memset(&data, 0, sizeof(t_data));

    // MiniLibX başlatma
    data.mlx = mlx_init();
    if (!data.mlx)
        return (1);

    // Haritayı oku ve kontrol et
    data.map = read_map("map.ber");
    if (!data.map)
    {
        mlx_destroy_display(data.mlx);
        free(data.mlx);
        return (1);
    }

    // XPM dosyalarını yükle ve kontrol et
    data.wall = mlx_xpm_file_to_image(data.mlx, "textures/wall.xpm", &img_width, &img_height);
    data.floor = mlx_xpm_file_to_image(data.mlx, "textures/floor.xpm", &img_width, &img_height);
    data.player = mlx_xpm_file_to_image(data.mlx, "textures/player.xpm", &img_width, &img_height);
    data.collect = mlx_xpm_file_to_image(data.mlx, "textures/collect.xpm", &img_width, &img_height);
    data.exit = mlx_xpm_file_to_image(data.mlx, "textures/exit.xpm", &img_width, &img_height);

    // Görüntü yükleme kontrolü
    if (!data.wall || !data.floor || !data.player || !data.collect || !data.exit)
    {
        close_window(&data);
        return (1);
    }

    // Pencere oluşturma
    data.win = mlx_new_window(data.mlx, 14 * TILE_SIZE, 6 * TILE_SIZE, "So Long");
    if (!data.win)
    {
        close_window(&data);
        return (1);
    }

    // Haritayı çiz
    draw_map(&data);

    // Olayları dinleme
    mlx_hook(data.win, 17, 0, close_window, &data);
    mlx_hook(data.win, 2, 1L << 0, key_press, &data);

    // Event loop
    mlx_loop(data.mlx);

    return (0);
}
/*Naıl oluyorda key_press e tek parametre girmemize rağmen 2 tane alıyor?
Burada bir olay gerçekleştiğinde, MLX kütüphanesi otomatik olarak uygun parametreleri fonksiyona gönderir. 
Sen sadece hangi fonksiyonun çağrılacağını ve ekstra bir parametre (param) belirtiyorsun.*/
