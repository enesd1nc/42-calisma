int check_map_walls(char **map, t_game *game)
{
    int i;
    
    // Check first and last rows
    i = 0;
    while (map[0][i] != '\0')
    {
        if (map[0][i] != '1')
            return (0);
        if (map[game->map_height - 1][i] != '1')
            return (0);
        i++;
    }
    
    // Check first and last columns
    i = 0;
    while (i < game->map_height)
    {
        if (map[i][0] != '1' || map[i][game->map_width - 1] != '1')
            return (0);
        i++;
    }
    return (1);
}
