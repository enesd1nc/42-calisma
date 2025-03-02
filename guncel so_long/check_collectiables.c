#include <stdlib.h>
#include <stdio.h>

void flood_fill(char **map, int x, int y, int *visited, int width, int height)
{
    if (x < 0 || x >= width || y < 0 || y >= height)
        return;
    if (map[y][x] == '1' || visited[y * width + x])
        return;
    
    visited[y * width + x] = 1;
    
    flood_fill(map, x + 1, y, visited, width, height);
    flood_fill(map, x - 1, y, visited, width, height);
    flood_fill(map, x, y + 1, visited, width, height);
    flood_fill(map, x, y - 1, visited, width, height);
}

int check_collectibles(char **map, int width, int height)
{
    int *visited = calloc(width * height, sizeof(int));
    int player_x = -1, player_y = -1;
    int i, j;
    
    // Oyuncunun konumunu bul
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            if (map[i][j] == 'P')
            {
                player_x = j;
                player_y = i;
                break;
            }
        }
        if (player_x != -1)
            break;
    }
    
    // Flood fill algoritması ile ulaşılabilir noktaları işaretle
    flood_fill(map, player_x, player_y, visited, width, height);
    
    // Tüm C'lerin ulaşılabilir olup olmadığını kontrol et
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            if (map[i][j] == 'C' && !visited[i * width + j])
            {
                free(visited);
                printf("Hata: Oyuncu tüm toplanabilir nesnelere ulaşamıyor!\n");
                return (0); // exit yerine return kullanıyoruz
            }
        }
    }
    
    free(visited);
    return (1);
}
