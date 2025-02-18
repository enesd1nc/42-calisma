#include <unistd.h>

int main(int ac, char *av[])
{
	if (ac ==  2)
	{
		int i = 0;
		while (av[1][i])
			i++;
		while(i > 0)
		{
			while(av[1][i] != 32 && i != 0)
				i--;
			if(av[1][i] == 32)
				i++;
			int sayac = 0;
			while(av[1][i] && av[1][i] != 32)
			{
				sayac++;
				write(1, &av[1][i], 1);
				i++;
			}
			i -= sayac + 2;
			if (i > 0)
				write(1, " ", 1);
		}
	}
	write(1, "\n", 1);	
}