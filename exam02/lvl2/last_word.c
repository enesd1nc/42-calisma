#include <unistd.h>

int main(int ac, char *av[])
{
	if (ac == 2)
	{
		int i = 0;
		while (av[1][i])
			i++;
		i -= 1;
		while (av[1][i] <= 32)
			i--;
		while (av[1][i] != 32 && av[1][i] != '\t' && i != 0)
			i--;
		if (i == 0)
			i--;
		while (av[1][++i])
			write(1, &av[1][i], 1);
	}
	write(1, "\n", 1);
}