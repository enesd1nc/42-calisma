#include <unistd.h>
#include <stdlib.h>

int main(int ac, char *av[])
{
    if (ac >= 2) // En az bir argüman varsa çalıştır
    {
        int i = 0, j = 0, flag = 0, start;
        char *s;

        // Baştaki boşlukları atla
        while (av[1][i] == ' ')
            i++;

        // İlk kelimenin başlangıç noktasını belirle
        start = i;

        // İlk kelimenin sonunu bul
        while (av[1][i] && av[1][i] != ' ')
            i++;

        // İlk kelimeyi saklamak için bellek ayır
        s = malloc(i - start + 1);
        if (!s)
            return (1);

        // İlk kelimeyi kopyala
        j = 0;
        while (start < i)
            s[j++] = av[1][start++];
        s[j] = '\0';

        // Kelimenin sonundan sonraki boşlukları atla
        while (av[1][i] == ' ')
            i++;

        // Kalan kelimeleri yazdır
        while (av[1][i])
        {
            flag = 1;
            write(1, &av[1][i], 1);

            // Birden fazla boşluğu atla
            if (av[1][i] == ' ')
            {
                while (av[1][i + 1] == ' ')
                    i++;
            }
            i++;
        }

        // Eğer en az bir kelime yazdırıldıysa, bir boşluk ekle
        if (flag == 1)
            write(1, " ", 1);

        // İlk kelimeyi sona yazdır
        j = 0;
        while (s[j])
        {
            write(1, &s[j], 1);
            j++;
        }

        // Belleği serbest bırak
        free(s);
    }
    write(1, "\n", 1);
    return (0);
}
