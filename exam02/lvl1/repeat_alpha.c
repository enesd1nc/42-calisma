#include <unistd.h>
int main(int ac, char *av[])
{
	int i = 0;
	int	d;
	int j = 0;
	int b;
	int z = 0;
	if (ac == 2)
	{
		while (av[1][i])
		{
			if (av[1][i] >= 'a' && av[1][i] <= 'z')
			{
				d = (av[1][i] - 'a') + 1;
				while (j < d)
				{
					write(1, &av[1][i], 1);
					j++;
				}
				j = 0;
			}
			else if (av[1][i] >= 'A' && av[1][i] <= 'Z')
			{
				b = (av[1][i] - 'A') + 1;
				while (z < b)
				{
					write(1, &av[1][i], 1);
					z++;
				}
				z = 0;
			}
			else
				write (1, &av[1][i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
}