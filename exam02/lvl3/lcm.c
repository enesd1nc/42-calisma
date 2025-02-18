unsigned int	lcm(unsigned int a, unsigned int b)
{
	if (a == 0 || b == 0)
		return (0);
	if (a == 1 || b == 1)
		return (a * b);
	int n = 1;
	while(n++)
	{
		if (n % a == 0 && n % b == 0)
			return (n);
	}
	
}
#include <stdio.h>
int main()
{
	printf("%d\n", lcm(6,4));
}
