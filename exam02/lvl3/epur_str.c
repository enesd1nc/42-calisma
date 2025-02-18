#include <unistd.h>

int	str_len(char *str)
{
	int i = 0;
	while(str[i])
		i++;
	return (i);
}

int main(int ac, char *av[])
{
	if (ac == 2)
	{
		int i = 0;
		int a;
		a = str_len(av[1]);
		a--;
		while (av[1][a] == 32)
			a--;
		while(av[1][i])
		{
			int flag = 1;
			while (av[1][i] == 32)
			{
				if (flag == 1 && i != 0 && i <= a)
					{
						write(1, " ", 1);
					}
				flag = 0;
				i++;
			}
			if (av[1][i] != '\0')// bu kontrol olmazssa eğer i null olarak gelip üstüne bide burda arttırılırsa while döngüsünde saçma sonuçlar çıkıyor
			{
				write(1, &av[1][i], 1);
				i++;	
			} 
		}
	}
	write(1, "\n", 1);
}