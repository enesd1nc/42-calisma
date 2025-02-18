#include <unistd.h>
int		len(char *str)
{
	int i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}
int main(int ac, char *av[])
{
	int d = len(av[1]);
	int i = 0;
	int j = len(av[1]);
	char	str[5];
	while (i < d / 2)
	{
		str[0] = av[1][i];
		av[1][i] = av[1][j - 1];
		av[1][j -1] = str[0];
		i++;
		j--;
	}
	int a = 0;
	while(av[1][a])
	{
		write(1, &av[1][a], 1);
		a++;
	}
	write(1, "\n",1);
}