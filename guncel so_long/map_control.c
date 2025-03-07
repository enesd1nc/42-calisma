#include "so_long.h"
#include <stdlib.h>
#include <stdio.h>

void    check_valid_chars(t_data *data, int height, int width)
{
    int i;
    int j;

    i = 0;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            if (data->map[i][j] != 'P' && data->map[i][j] != 'E' && 
                data->map[i][j] != 'C' && data->map[i][j] != '0' &&
                data->map[i][j] != '1')
            {
                printf("Error\nInvalid character in map!\n");
                close_window(data);  // Use close_window instead of just free_map
                exit(1);
            }
            j++;
        }
        i++;
    }
}
