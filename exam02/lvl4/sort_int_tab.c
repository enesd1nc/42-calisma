//Bubble sort kullandık

void	sort_int_tab(int *tab, unsigned int size)
{
	int i = 0;
	int temp;
	while (i < size - 1)
	{
		int j = 0;
		while (j < size - i - 1)
		{
			if (tab[j] > tab[j + 1])
			{
				temp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}
#include <stdio.h>
int main()
{
	int	tab[] = {3,2,1};
	sort_int_tab(tab, 3);
	int i = 0;
	while (i < 3)
	{
		printf("%d\n", tab[i]);
		i++;
	}
}