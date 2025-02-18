#include <unistd.h>

int	atoi(char *str)
{
	int i = 0;
	int r = 1;
	int	result = 0;
	while (str[i] <= 32)
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
	{
		r *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		result = (str[i] - '0') + 10 * result;
		i++;
	}
	return (result * r);
}
int	prime(int i)
{
	if (i < 2)
		return (0);
	int a = 2;
	while (a < i)
	{
		if (i % a == 0)
			return (0);
		a++;
	}
	return (1);
}
void	print(int nbr)
{
	char	c;
	if (nbr > 9)
		print(nbr / 10);
	c = (nbr % 10) + '0';
	write (1, &c, 1);
}

int main(int ac, char *av[])
{
	if (ac == 2)
	{
		int hiding;
		hiding = atoi(av[1]);
		int i = 2;
		int counter = 0;
		while (i <= hiding)
		{
			if (prime(i) == 1)
				counter += i;
			i++;
		}
		print(counter);
	}
	write(1, "\n", 1);
}