#include <stdlib.h>

char	*ft_strdup(char *src)
{
	int i;
	int len;
	while (src[i])
		i++;
	len = i;
	i = 0;
	char	*ptr;
	ptr = malloc(len + 1);
	while (src[i])
	{
		ptr[i] = src[i];
		i++;
	}
	ptr[i] = '\0';
	return(ptr);
}
#include <stdio.h>
int main()
{
	printf("%s\n", ft_strdup("enes"));
}