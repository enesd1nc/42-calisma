int	ft_value(char s)
{
	if (s >= 'a' && s <= 'z')
		return (s - 'a' + 10);
	else if (s >= 'A' && s <= 'Z')
		return (s - 'A' + 10);
	else if (s >= '0' && s <= '9')
		return (s - '0');
}

int ft_atoi_base(const char *str, int str_base)
{
	int sign = 1;
	int result = 0;
	if(*str == '-')
	{
		sign *= -1;
		str++;
	}
	int value;
	while (*str)
	{
		value = ft_value(*str);
		result = result * str_base + value;
		str++;
	}
	return (result * sign);
}
#include <stdio.h>
int main()
{
	printf("%d\n", ft_atoi_base("a", 16));
}