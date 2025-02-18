char	*ft_strpbrk(const char *s1, const char *s2)
{
	int i = 0;
	
	while (s1[i])
	{
		int j = 0;
		while (s2[j])
		{
			if (s1[i] == s2[j])
				return ((char *)&s1[i]);
			j++;
		}
		i++;
	}
	return (0);
}
#include <stdio.h>
int main()
{
	char	s1[] = "enes";
	char	s2[] = "as";
	printf("%c\n", *ft_strpbrk(s1,s2));
}