#include <stdio.h>
#include <stdlib.h>

int main(int ac, char *av[])
{
	if (ac == 4)
	{
		int sonuc;
		int i = 0;
		int d = atoi(av[1]);
		int c = atoi(av[3]);
		if (av[2][0] == '*')
			sonuc = d * c;
		if (av[2][0] == '/')
			sonuc = d / c;
		if (av[2][0] == '+')
			sonuc = d + c;
		if (av[2][0] == '-')
			sonuc = d - c;
		printf("%d\n", sonuc);
	}
}