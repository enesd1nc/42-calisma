#include <stdlib.h>

char    **ft_split(char *str)
{
	char	**ptr;
	ptr = (char **)malloc(sizeof(char *) * 1000);
	int i = 0;
	
	int j = 0;
	while (str[i])
	{
		while (str[i] <= 32)
			i++;
		int k = 0;
		ptr[j] = malloc(sizeof(char) * 1000);
		while (str[i] > 32)
		{
			ptr[j][k++] = str[i++];
		}
		ptr[j][k] = '\0';
		j++;
	}
	return (ptr);
}
#include <stdio.h>
int main()
{
	char	*str = "enes dinc";
	int i = 0;
	while (i < 2)
	{
		printf("%s\n", ft_split(str)[i]);
		i++;
	}
}