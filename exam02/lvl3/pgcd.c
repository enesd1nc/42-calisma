#include <stdio.h>
#include <stdlib.h>
int main(int ac, char *av[])
{
	int	a;
	int	b;
	int	n;	
	if (ac == 3)
	{
		a = atoi(av[1]);
		b = atoi(av[2]);
		if (a < b)
			n = a + 1;
		else 
			n = b + 1;
		while (n--)
		{
			if(a % n == 0 && b % n == 0)
				break;
		}
		printf("%d", n);
	}
	printf("\n");
}