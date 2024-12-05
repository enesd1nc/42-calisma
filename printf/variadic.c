#include <stdarg.h>
#include "ft_printf.h"
int	topla(int a, ...)
{
	va_list liste;
	va_start(liste, a);//son sabit değişkeni girmek değişken parametrelerin nerede başladıgını belirtmek için referansdır 
	int toplam = 0;
	for(int i = 0; i < a; i++)
	{
		toplam += va_arg(liste, int);//her çağırılmada pozisyon okuması yaparak diğer parametreye geçer.böylece her bir parametrenin değerini alır.
	}
	return (toplam);
}
int main()
{
	ft_printf("%d\n", topla(3,1,2,3));
}