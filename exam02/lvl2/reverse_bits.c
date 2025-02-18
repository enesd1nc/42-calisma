unsigned char	reverse_bits(unsigned char octet)
{
	unsigned char bit = 0;
	int i = 0;
	while (i++ < 8)
	{
		bit = (bit << 1) | (octet & 1);
		octet = octet >> 1; 
	}
	return (bit);
}
/*burada octetin en sağından itibaren tek tek bitler alınıp bit değiişkeninin en sağına atılıyor  
her seferinde bit değişkeni bir sola kaydırılıyor  böylece ilk yazılan yani octetin en sağındaki en sola gelmiş oluyor*/