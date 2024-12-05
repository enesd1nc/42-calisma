#include "ft_printf.h"
#include <stdio.h>
#include <stddef.h>

int main()
{
	char	a = 'a';
	char	*s = NULL;
	printf("%c %s %d %i %u %p %x %X %%\n", 'c', s, 12, 31, -2, s, 255, 255);
	ft_printf("%c %s %d %i %u %p %x %X %%\n", 'c', s, 12, 31, -2, s, 255, 255);
}
//unsigned int e - li değer girildiği zaman 1 e tümleme yapar yani 0 olan bitleri 1  1 olan bitleri ise 0 yapar