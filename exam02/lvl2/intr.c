#include <unistd.h>

int main(int ac, char *av[])
{
	if (ac == 3)
	{
	int i = 0;
	char	print[128] = {0};// tüm elemanları ascii olarak 0 yapar yani null
		while (av[1][i])
		{
			int j = 0;
			while (av[2][j])
			{
				if (av[2][j] == av[1][i] && !print[av[1][i]])
					{
						write(1, &av[1][i], 1);
						print[av[1][i]] = 1;
					}
				j++;
			}
			i++;
		}
	}
	write(1, "\n", 1);
}