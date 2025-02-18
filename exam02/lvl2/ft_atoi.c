int	ft_atoi(const char *str)
{
	int res = 0;
	int i = 0;
	int	e = 1;
	while (str[i] <= 32)
		i++;
	if (str[i] == '-')
	{
		e *= -1;
		i++;
	}
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (str[i] - '0') + 10 * res;
		i++;
	}
	return (res * e);
}
#include <stdio.h>

int main()
{
	printf("%d\n", ft_atoi("-123"));
}