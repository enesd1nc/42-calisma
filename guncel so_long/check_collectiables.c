#include <stdlib.h>
#include <stdio.h>

void flood_fill(char **map, int x, int y, int *visited, int width, int height, int check_collectibles)
{
    if (x < 0 || x >= width || y < 0 || y >= height || !map || !map[y])
        return;
    if (map[y][x] == '1' || visited[y * width + x])
        return;
    // Collectible kontrolü yaparken E'yi engel olarak görme
    if (check_collectibles && map[y][x] == 'E')
        return;
    
    visited[y * width + x] = 1;
    
    flood_fill(map, x + 1, y, visited, width, height, check_collectibles);
    flood_fill(map, x - 1, y, visited, width, height, check_collectibles);
    flood_fill(map, x, y + 1, visited, width, height, check_collectibles);
    flood_fill(map, x, y - 1, visited, width, height, check_collectibles);
}

int check_collectibles(char **map, int width, int height)
{
    if (!map || width <= 0 || height <= 0)
        return (0);
        
    int *visited = calloc(width * height, sizeof(int));
    int *visited_exit = calloc(width * height, sizeof(int));
    int player_x = -1, player_y = -1;
    int exit_found = 0;
    int i, j;
    
    if (!visited || !visited_exit)
    {
        free(visited);
        free(visited_exit);
        return (0);
    }
    
    // Önce tüm haritayı tara
    for (i = 0; i < height; i++)
    {
        if (!map[i]) continue;
        for (j = 0; j < width; j++)
        {
            if (map[i][j] == 'P')
            {
                player_x = j;
                player_y = i;
            }
            else if (map[i][j] == 'E')
            {
                exit_found = 1;
            }
        }
    }
    
    if (player_x == -1)
    {
        free(visited);
        free(visited_exit);
        printf("Hata: Oyuncu (P) bulunamadı!\n");
        return (0);
    }
    
    if (!exit_found)
    {
        free(visited);
        free(visited_exit);
        printf("Hata: Çıkış (E) bulunamadı!\n");
        return (0);
    }

    // İlk flood fill: Collectible'lar için
    flood_fill(map, player_x, player_y, visited, width, height, 1);
    // İkinci flood fill: Exit için
    flood_fill(map, player_x, player_y, visited_exit, width, height, 0);
    
    // Kontroller
    for (i = 0; i < height; i++)
    {
        if (!map[i]) continue;
        for (j = 0; j < width; j++)
        {
            if (map[i][j] == 'C' && !visited[i * width + j])
            {
                free(visited);
                free(visited_exit);
                printf("Hata: Oyuncu tüm toplanabilir nesnelere ulaşamıyor!\n");
                return (0);
            }
            if (map[i][j] == 'E' && !visited_exit[i * width + j])
            {
                free(visited);
                free(visited_exit);
                printf("Hata: Oyuncu çıkışa ulaşamıyor!\n");
                return (0);
            }
        }
    }
    
    free(visited);
    free(visited_exit);
    return (1);
}
