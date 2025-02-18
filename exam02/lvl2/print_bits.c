#include <unistd.h>

void	print_bits(unsigned char octet)
{
	int i = 8;
	unsigned char bit;
	while (i--)
	{
		bit = (octet >> i & 1) + '0';
		write(1, &bit, 1);
	}
}
int main()
{
	print_bits(5);
	write(1, "\n", 1);
}
/*octetin en solundakine bakıyoruz  tek tek 
0000 0101 >> 7 = 0000 0000 sağdan itibaren 7 tanesini sildik sola 7 tane sıfır ekledik böylece en soldaki en sağa geldi şimdi 1 ile kıyaslayacağız
0000 0000 & 0000 0001 = 0000 0000 0000 burdan 0 yazdırılır
0000 0101 >> 2 kez kaymış olsun busefer
0000 0001 & 0000 0001 = 1 yazdırılır. */