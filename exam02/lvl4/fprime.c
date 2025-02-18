#include <stdio.h>
#include <stdlib.h>

int prime(int i)
{
	int a = 2;
	while(a < i)
	{
		if (i % a == 0)
			return (0);
		a++;
	}
	return (1);
}

int main(int ac, char *av[])
{
	if (ac == 2)
	{
		int i = 2;
		int nbr;
		int counter = 1;
		int a;
		nbr = atoi(av[1]);
		a = nbr;
		while (i <= nbr)
		{
			while (prime(i) && nbr % i == 0)
			{
				counter *= i;
				printf("%d", i);
				nbr = nbr / i;
				if (a != counter)
					printf("*");
			}
			i++;
		}
	}
	printf("\n");
}