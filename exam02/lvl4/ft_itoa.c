#include <stdlib.h>
int	lenght(int nbr)
{
	int i = 0;
	if (nbr < 0)
	{
		nbr *= -1;
		i++;
	}
	if (nbr == 0)
		i++;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int nbr)
{
	char	*str;
	str = malloc(lenght(nbr) * sizeof(char) + 1);
	int i;
	i = lenght(nbr);
	str[i] = '\0';
	if (nbr < 0)
	{
		str[0] = '-';
		nbr *= -1;
	}
	if (nbr == 0)
		str[0] = '0';
	while (nbr != 0)
	{
		str[--i] = (nbr % 10) + '0';
		nbr /= 10;
	}
	
	return (str);
	
}
#include <stdio.h>
int main()
{
	printf("%s\n", ft_itoa(123));
}