char    *ft_strrev(char *str)
{
	int i = 0;
	char temp;
	while (str[i])
		i++;
	int len;
	len = i;
	i = 0;
	int j;
	j = len;
	while (i < len / 2)
	{
		temp = str[i];
		str[i] = str[j - 1];
		str[j - 1] = temp;
		i++;
		j--;
	}
	return (str);
}
#include <stdio.h>
int main()
{
	char	str[] = "enes";
	printf("%s\n", ft_strrev(str));
}