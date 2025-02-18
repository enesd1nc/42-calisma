#include <stddef.h>
size_t	ft_strspn(const char *s, const char *accept)
{
	int j = 0;
	size_t i = 0;
	while (s[i] == accept[j])
	{
		i++;
		j++;
	}
	return (i);
}
#include <stdio.h>
#include <string.h>
int main()
{
	char	s[] = "abcdefg";
	char	d[] = "abcd";
	printf("%ld\n", ft_strspn(s, d));
	printf("%ld\n", strspn(s,d));
}