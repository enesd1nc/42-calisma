/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdinc <mdinc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:59:02 by mdinc             #+#    #+#             */
/*   Updated: 2025/02/17 23:01:38 by mdinc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>

void	ft_putnbr(int nbr)
{
	char	c;
	
	if (nbr > 9)
		ft_putnbr(nbr / 10);
	c = (nbr % 10) + '0';
	write(1, &c, 1);
}

void	handle_signal(int sig)
{
	static int	bit_counter = 7; // normalde tanımlama ile atama farklı yerlerde yapılır norminettede.Fakat staticde farklı yerde yaparsan static çalışmaz
	                             //her atama yerini gordugunde o değeri alır kaldığı yerden devam etmez.
	static char	rec_char = 0;
	
	 if (sig == 12)
	{
		rec_char = rec_char | (1 << bit_counter);
	}
	bit_counter--;
	if (bit_counter == -1)
	{
		write(1, &rec_char, 1);
		bit_counter = 7;
		rec_char = 0;
	}
}

int	main(void)
{
	write(1, "process id: ", 12);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	signal(10, handle_signal);
	signal(12, handle_signal);
	while (1)
	{
		pause();
	}
	return (0);
}
