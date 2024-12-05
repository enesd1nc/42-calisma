#include <unistd.h>

int	ft_putchar(char c)
{
	if (write(1, &c, 1) == -1)//karakteri yazdır ve hata kontrolü
		return (-1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		if (write(1, "(null)", 6) == -1)
			return (-1);
		return (6);//(null) un baytı
	}
	while (str[i])
	{
		if (ft_putchar(str[i]) == -1)
			return (-1);
		i++;
	}
	return (i);
}
/*write fonsiyonu yazdırılan metnin baytını dondurur
eger bir hata olurda yazdıramazssa -1 dondurur*/