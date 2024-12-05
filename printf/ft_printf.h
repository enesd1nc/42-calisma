#ifndef FT_PRINTF_H
# define FT_PRINTF_H

int	ft_putchar(char c);
int	ft_putstr(char *str);
int	ft_putint(int n);
int	ft_putuint(unsigned int n);
int	ft_puthex(unsigned int n, char c);
int	ft_putptr(unsigned long n);
int	ft_printf(const char *format, ...);

#endif