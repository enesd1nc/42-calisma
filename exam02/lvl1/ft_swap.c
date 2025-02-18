void	ft_swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
#include <stdio.h>
int main()
{
	int a = 5;
	int b = 10;
	ft_swap(&a,&b);
	printf("%d", a);
}