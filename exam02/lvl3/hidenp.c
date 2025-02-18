#include <unistd.h>

int	len(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

int main(int ac, char *av[])
{
	if (ac == 3)
	{
		int	sayac = 0;
		int j = -1;
		int i = 0;
		while (av[1][i])
		{
			while(av[2][++j])
			{
				if (av[1][i] == av[2][j])
				{
					sayac += 1;
					break;
				}
			}
			i++;
		}
		if (sayac == len(av[1]))
			write(1, "1", 1);
		else
			write(1, "0", 1);
	}
	write(1, "\n", 1);
}