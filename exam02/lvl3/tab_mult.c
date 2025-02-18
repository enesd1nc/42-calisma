#include <unistd.h>

int	ft_atoi(char *str)
{
	int rest = 0;
	while(*str >= '0' && *str <= '9')
	{
		rest = (*str - '0') + rest * 10;
		str++;
	}
	return (rest);
}

void	putnbr(int n)
{
	char	c;
	if (n > 9)
		putnbr(n / 10);
	c = (n % 10) + '0';
	write(1, &c, 1);
}

int main(int ac, char *av[])
{
	if (ac == 2)
	{
		int a = 1;
		int nbr;
		int result;
		nbr = ft_atoi(av[1]);
		while (a < 10)
		{
			putnbr(a);
			write(1, " x ", 3);
			putnbr(nbr);
			write(1, " = ", 3);
			result = a * nbr;
			putnbr(result);
			if (a < 9)
				write(1, "\n", 1);
			a++;
		}
	}
	write(1, "\n", 1);
}