#include <unistd.h>

int	str_len(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

int main(int ac, char *av[])
{
	if (ac > 1)
	{
		int j = 1;
		while (j < ac)
		{
			int i = str_len(av[j]);
			while (--i > -1)
			{
				while (av[j][i] <= 32)
					i--;
				if ((av[j][i] >= 'a' && av[j][i] <= 'z') || (av[j][i] >= 'A' && av[j][i] <= 'Z'))
				{
					if(av[j][i] >= 'a' && av[j][i] <= 'z')
						av[j][i] -= 32;
					i--;
				}
				while (av[j][i] > 32)
				{
					if (av[j][i] >= 'A' && av[j][i] <= 'Z')
						av[j][i] += 32;
					i--;
				}
			}
			int a = 0;
			while (av[j][a])
			{
				write(1, &av[j][a], 1);
				a++;
			}
			j++;
			if(j < ac)
				write(1, "\n", 1);
		}
	}
	write(1, "\n", 1);
}