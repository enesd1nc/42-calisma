#include "ft_printf.h"

int	ft_puthex(unsigned int n, char c)
{
	char	hex;
	int		len;
	int		temp;

	len = 0;
	if (n >= 16)
	{
		temp = ft_puthex(n / 16, c);
		if (temp == -1)
			return (-1);
		len += temp;
	}
	if (c == 'x')
		hex = "0123456789abcdef"[n % 16];//sol tarafda bir dizi var bu diznin n in 16 ya modundan çıkan sonuç kadar öteliyoruz gelen elemanı hex e atıyoruz
		//örneğin 15 çıktı f elemanını verir.
	if (c == 'X')
		hex = "0123456789ABCDEF"[n % 16];
	if (ft_putchar(hex) == -1)
		return (-1);
	return (len + 1);
}