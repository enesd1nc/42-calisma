#include "ft_printf.h"

static int	ft_putptr_helper(unsigned long n)
{
	char	hex;
	int		len;
	int		temp;

	len = 0;
	if (n >= 16)
	{
		temp = ft_putptr_helper(n / 16);
		if (temp == -1)
			return (-1);
		len += temp;
	}
	hex = "0123456789abcdef"[n % 16];
	if (ft_putchar(hex) == -1)
		return (-1);
	return (len + 1);
}

int	ft_putptr(unsigned long n)
{
	int	len;
	int	temp;

	if (n == 0)// c dilinde boş bir işaretçi 0 ilede ifade edilebilir (NULL)
	{
		if (ft_putstr("(nil)") == -1)
			return (-1);
		return (5);
	}
	if (ft_putchar('0') == -1 || ft_putchar('x') == -1)
		return (-1);
	len = 2;
	temp = ft_putptr_helper(n);
	if (temp == -1)
		return (-1);
	len += temp;
	return (len);
}
// %p işaretçinin tuttuğu adresi hexadecimal formatta yazırır
//adreslerin 0x ile başlamasının nedeni 16 lık sayı sistemi oldugunu belirtmektir.