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

typedef struct s_pos {
    int x;
    int y;
} t_pos;

static t_pos find_player(char **map, int width, int height, int *exit_found)
{
    t_pos player = {-1, -1};
    int i, j;

    for (i = 0; i < height; i++)
    {
        if (!map[i]) 
            continue;
        for (j = 0; j < width; j++)
        {
            if (map[i][j] == 'P')
            {
                player.x = j;
                player.y = i;
            }
            else if (map[i][j] == 'E')
                *exit_found = 1;
        }
    }
    return (player);
}

static int check_map_validity(t_pos player, int exit_found)
{
    if (player.x == -1)
    {
        printf("Hata: Oyuncu (P) bulunamadı!\n");
        return (0);
    }
    if (!exit_found)
    {
        printf("Hata: Çıkış (E) bulunamadı!\n");
        return (0);
    }
    return (1);
}

static int perform_checks(char **map, int *visited, int *visited_exit, 
                        int width, int height)
{
    int i, j;

    for (i = 0; i < height; i++)
    {
        if (!map[i]) 
            continue;
        for (j = 0; j < width; j++)
        {
            if (map[i][j] == 'C' && !visited[i * width + j])
            {
                printf("Hata: Oyuncu tüm toplanabilir nesnelere ulaşamıyor!\n");
                return (0);
            }
            if (map[i][j] == 'E' && !visited_exit[i * width + j])
            {
                printf("Hata: Oyuncu çıkışa ulaşamıyor!\n");
                return (0);
            }
        }
    }
    return (1);
}

int check_collectibles(char **map, int width, int height)
{
    if (!map || width <= 0 || height <= 0)
        return (0);
    int *visited = calloc(width * height, sizeof(int));
    int *visited_exit = calloc(width * height, sizeof(int));
    int exit_found = 0;
    if (!visited || !visited_exit)
    {
        free(visited);
        free(visited_exit);
        return (0);
    }
    t_pos player = find_player(map, width, height, &exit_found);
    if (!check_map_validity(player, exit_found))
    {
        free(visited);
        free(visited_exit);
        return (0);
    }
    flood_fill(map, player.x, player.y, visited, width, height, 1);
    flood_fill(map, player.x, player.y, visited_exit, width, height, 0);
    int result = perform_checks(map, visited, visited_exit, width, height);
    free(visited);
    free(visited_exit);
    return (result);
}
