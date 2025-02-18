unsigned char	swap_bits(unsigned char octet)
{
	return ((octet >> 4) | (octet << 4));
}
/*0100 0001 4 biti yer değiştirecez
octet >> 4 = 0000 0100
octet << 4 = 0001 0000
bunları veya ile toplarsak
0001 0100 sonucunu elde ederiz.*/
