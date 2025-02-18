#include <unistd.h>

int	ft_atoi(char *str)
{
	int rest = 0;
	int i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		rest = (str[i] - '0') + rest * 10;
		i++;
	}
	return (rest);
}
void	put_hex(int n)
{
	char	c;
	if (n > 16)
		put_hex(n / 16);
	c = "0123456789abcdef"[n % 16];
	write(1, &c, 1);
	
}

int main(int ac, char *av[])
{
	if (ac == 2)
	{
		int d;
		d = ft_atoi(av[1]);
		put_hex(d);
	}
	write(1, "\n", 1);
}