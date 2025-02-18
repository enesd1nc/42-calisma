#include <unistd.h>

int main(int ac, char *av[])
{
	if (ac > 1)
	{
		int j = 1;
		while (j < ac)
		{
			int i = 0;
			while(av[j][i])
			{
				if (av[j][i] >= 'a' && av[j][i] <= 'z')
				{
					av[j][i] -= 32;
					i++;
				}
				while(av[j][i] > 32)
				{
					if(av[j][i] >= 'A' && av[j][i] <= 'Z' && av[j][i - 1] != 32)
						av[j][i] += 32;
					i++;
				}
				while(av[j][i] == 32)
					i++;
			}
			i = 0;
			while(av[j][i])
			{
				write(1, &av[j][i], 1);
				i++;
			}
			j++;
			if (j < ac)
				write(1, "\n", 1);
		}
	}
	write(1, "\n", 1);
}
