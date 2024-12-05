#include <unistd.h>
#include <stdio.h>

int	ft_putint(int n)
{
	long	nb;
	int		len;
	int		tmp;
	char	c;

	len = 0; // Toplam uzunluk için başlatma
	nb = (long)n;
	if (nb < 0)
	{
		if (write(1, "-", 1) == -1)
			return (-1);
		nb *= -1;
		len++;
	}
	if (nb >= 10)
	{
	 	tmp = ft_putint(nb / 10); // Rekürsif çağrıdan gelen uzunluk
		if (tmp == -1)
			return (-1);
		len += tmp; // Uzunluğu biriktir
	}
	c = nb % 10 + '0'; // Son basamağı hesapla
	if (write(1, &c, 1) == -1)
		return (-1);
	len++;
	return (len); // Toplam uzunluğu döndür
}

int	ft_putuint(unsigned int n)
{
	long	nb;
	int		len;
	int		tmp;
	char	c;

	len = 0;
	nb = (long)n;
	if (nb >= 10)
	{
		tmp = ft_putuint(nb / 10);
		if (tmp == -1)
			return (-1);
		len += tmp;
	}
	c = ((nb % 10) + '0');
	if (write(1, &c, 1) == -1)
		return (-1);
	len++;
	return (len);
}

/*recursive fonksiyonlarda fonksiyon başa dönüp işlemini tamamladıktan sonra kaldığı yerden devam eder
örneğin: 42 girdiğimiz zaman 4 başa gider fonksiyonu tamamlar 
ardından bir sonraki adım olan ft_putint(nb %10) dan nb = 42 değerinden (ilk çağrı) devam eder
!! Her fonksiyon çağrısındaki yerel değişkenler birbirinden bağımsızdır bu yüzden bir üst çağrıya dönerken leni 0 olarak alıyoruz*/