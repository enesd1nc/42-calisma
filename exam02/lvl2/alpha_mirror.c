#include <unistd.h>

int main(int ac, char *av[])
{
	if (ac == 2)
	{
		int	d;
		int i = 0;
		while (av[1][i])
		{
			if (av[1][i] >= 'a' && av[1][i] <= 'z')
			{
				d = av[1][i] - 'a';
				av[1][i] += 25 - 2*d;
			}
			else if (av[1][i] >= 'A' && av[1][i] <= 'Z')
			{
				d = av[1][i] - 'A';
				av[1][i] += 25 - 2*d;
			}
			write(1, &av[1][i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
}