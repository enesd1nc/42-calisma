#include "get_next_line/get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h> 
#include "so_long.h" // close fonksiyonu için gerekli
#include <stdio.h>

int	str_len(char *str)
{
	int i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int count_lines(char *filename)
{
	int fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	char *line;
	int count = 0;
	while ((line = get_next_line(fd)))
	{
		count++;
		free(line);
	}
	close(fd);
	return (count);
}

int get_line_len(char *line)
{
    int len = 0;
    while (line[len] && line[len] != '\n' && line[len] != '\r')
        len++;
    return len;
}

char **read_map(char *map)
{
    // Değişken tanımlamaları
    int     fd;
    char    *line;
    char    **rest;
    int     j;
    int     counter1 = 0;  // Exit sayısı için sayaç
    int     counter2 = 0;  // Player sayısı için sayaç
    int     counter3 = 0;  // Collectible sayısı için sayaç
    int     line_count = count_lines(map);  // Haritadaki toplam satır sayısı
    int     first_line_len = 0;  // İlk satırın uzunluğu (haritanın genişliği)

    // Harita dosyası kontrolü
    if (line_count <= 0)
    	return (NULL);

    // Harita dosyasını aç
    j = 0;
    fd = open(map, O_RDONLY);
    if (fd < 0)
        return (NULL);
    
    // Harita için ana bellek ayrılması
    rest = (char **)calloc((line_count + 1), sizeof(char *));
    if (!rest)
    {
        close(fd);
        return (NULL);
    }

    // İlk satırı oku ve kontrol et
    line = get_next_line(fd);
    if (!line)
    {
        free(rest);
        close(fd);
        return (NULL);
    }
    
    // İlk satırın uzunluğunu al (tüm satırlar bu uzunlukta olmalı)
    first_line_len = get_line_len(line);
    while (line && j < line_count)
    {
        // Her satırın uzunluğunu kontrol et (dikdörtgen harita için)
        int current_len = get_line_len(line);
        if (current_len != first_line_len)
        {
            free_map(rest);
            free(line);
            close(fd);
            return (NULL);
        }

        // Her satır için bellek ayır
        rest[j] = (char *)calloc(first_line_len + 1, sizeof(char));
        if (!rest[j])
        {
            free_map(rest);
            free(line);
            close(fd);
            return (NULL);
        }

        // Satırı karakter karakter işle
        int k = 0;
        while (k < first_line_len)
        {
            // İlk ve son satırın tamamen duvar olması kontrolü
            if ((j == 0 || j == line_count - 1) && line[k] != '1')
            {
                free_map(rest);
                free(line);
                close(fd);
                return (NULL);
            }

            // Her satırın başı ve sonunun duvar olması kontrolü
            if ((k == 0 || k == first_line_len - 1) && line[k] != '1')
            {
                free_map(rest);
                free(line);
                close(fd);
                return (NULL);
            }

            // Karakteri haritaya yerleştir ve gerekli sayaçları güncelle
            rest[j][k] = line[k];
            if (line[k] == 'E')  // Exit sayısı
                counter1++;
            if (line[k] == 'P')  // Player sayısı
                counter2++;
            if (line[k] == 'C')  // Collectible sayısı
                counter3++;
            k++;
        }
        rest[j][k] = '\0';  // Satır sonunu işaretle
        free(line);
        line = get_next_line(fd);  // Sonraki satırı oku
        j++;
    }

    // Harita geçerlilik kontrolü: 
    // - Tüm satırlar okundu mu?
    // - Tam olarak 1 Exit var mı?
    // - Tam olarak 1 Player var mı?
    // - En az 1 Collectible var mı?
    if (j != line_count || counter1 != 1 || counter2 != 1 || counter3 < 1)
    {
        free_map(rest);
        close(fd);
        return (NULL);
    }

    close(fd);
    return (rest);
}
/*#include <stdio.h>
int main()
{
	char	**str;
	int j = 0;
	str = read_map("map.ber");
	while(j < 6)
	{
		printf("%s", str[j++]);
	}
	printf("\n");
}
*/