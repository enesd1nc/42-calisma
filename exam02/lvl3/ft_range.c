#include <stdlib.h>

int     *ft_range(int start, int end)
{
	int size;
	int *p;
	if (start == 0 && end == 0)
		size = 1;
	else if (start <= end)
		size = end - start +1;
	else
		size = start - end +1;
	p = (int *)malloc(sizeof(int) * size);
	int i = 0;
	if (start == 0 && end == 0)
	{
		p[i] = 0;
		return(p);
	}
	if (start <= end)
	{
		while (start <= end)
		{
			p[i++] = start++;
		}
	}
	else
	{
		while (end <= start)
			p[i++] = start--;
	}
	return (p);
}
#include <stdio.h>

int main()
{
	int	*p;
	p = ft_range(-1,2);
	int i = 0;
	while (i < 4)
	{
		printf("%d\n", p[i]);
		i++;
	}
}