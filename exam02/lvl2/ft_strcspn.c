#include <stddef.h>
size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t i = 0;
	int j = 0;
	while(s[i])
	{
		while (s[i] != reject[j] && reject[j])
			j++;
		if (s[i] == reject[j])
			return (i);
		j = 0;
		i++;
	}
	return (i);
}
#include <stdio.h>
int main()
{
	printf("%ld\n", ft_strcspn("enes", "A"));
}