

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct s_data
{
    void *mlx;
    void *win;
}   t_data;

int close_window(t_data *data)
{
    mlx_destroy_window((*data).mlx, (*data).win);//data->mlx şeklindede yazılabilir.structk içideki üye değişkene pointer aracılığıyla erişmek için kullanılır.
    mlx_destroy_display(data->mlx);  // MiniLibX kaynaklarını serbest bırak
    free(data->mlx);  // Mlx işaretçisini serbest bırak
	exit(0);
}
int key_press(int keycode, t_data *data)
{
    if (keycode == 65307) // ESC tuşu
    {
        close_window(data);
        exit(0);
    }
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

int main()
{
    t_data data;

    // MiniLibX başlatma
    data.mlx = mlx_init();
    if (!data.mlx)
        return (1);

    // Pencere oluşturma
    data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "MiniLibX Text");
    if (!data.win)
        return (1);

    // Yazıyı ekrana yazdırma
    mlx_string_put(data.mlx, data.win, WIDTH / 2 - 50, HEIGHT / 2, 0xFFFFFF, "Hello, Elif");

    // Olayları dinleme
    mlx_hook(data.win, 17, 0, close_window, &data);  // Pencereyi kapatma butonu
	mlx_hook(data.win, 2, 1L << 0, key_press, &data);


    // Event loop
    mlx_loop(data.mlx);

    return (0);
}
/*Naıl oluyorda key_press e tek parametre girmemize rağmen 2 tane alıyor?
Burada bir olay gerçekleştiğinde, MLX kütüphanesi otomatik olarak uygun parametreleri fonksiyona gönderir. 
Sen sadece hangi fonksiyonun çağrılacağını ve ekstra bir parametre (param) belirtiyorsun.*/
