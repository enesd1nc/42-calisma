#include <stdlib.h>

int     *ft_rrange(int start, int end)
{
	int	*p;
	int size;

	if (start <= end)
		size = end - start +1;
	else
		size = start - end +1;
	p = (int *)malloc(sizeof(int) * size);
	int i = 0;
	if (start <= end)
	{
		while (start <= end)
			p[i++] = end--;
	}
	else 
	{
		while(end <= start)
			p[i++] = end++;
	}
	return (p);
}
#include <stdio.h>

int main()
{
	int	*p;
	p = ft_rrange(1,-1);
	int i = 0;
	while (i < 3)
	{
		printf("%d\n", p[i]);
		i++;
	}
}