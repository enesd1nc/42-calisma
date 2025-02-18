int max(int *tab, unsigned int len)
{
	int i = 0;
	int result; 
	result = tab[i];
	while (i < len - 1)
	{
		i++;
		if (result < tab[i])
			result = tab[i];
	}
	return (result);
}
#include <stdio.h>
int main()
{
	int	a[] = {5,9,11,10};
	printf("%d\n", max(a, 4));
}
