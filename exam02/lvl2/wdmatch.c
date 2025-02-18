#include <unistd.h>

int	str_len(char *str)
{
	int i = 0;
	while(str[i])
		i++;
	return (i);
}

int	check_word(char *s1, char *s2)
{
	int	i = 0;
	int	j = 0;
	int	d;
	d = str_len(s1);
	int	counter;
	while(s1[i])
	{
		while(s2[j])
		{
			if (s1[i] == s2[j])
				{
					counter++;
					j++;
					break;
				}
			j++;	
		}
		i++;
	}
	if (counter == d)
		return (1);
	return (0);
}

int main(int ac, char *av[])
{
	if (ac == 3)
	{
		int a;
		int i = 0;
		a = check_word(av[1], av[2]);
		if (a == 1)
		{
			while(av[1][i])
			{
				write(1, &av[1][i], 1);
				i++;
			}
		}
	}
	write(1, "\n", 1);
}