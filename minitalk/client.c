/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdinc <mdinc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:58:42 by mdinc             #+#    #+#             */
/*   Updated: 2025/02/19 14:59:10 by mdinc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

static int	ft_atoi(char *s)
{
	int	nbr;
	int	i;

	i = 0;
	nbr = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1);
		nbr = nbr * 10 + (s[i] - '0');
		i++;
	}
	return (nbr);
}
//en büyük bitden itibaren gönderdik
static void	get_bit(char *message, int server_pid)
{	
	int		i;
	int		j;

	i = 0;
	while (message[i])
	{
		j = 8;
		while (j--)
		{
			if ((message[i] >> j) & 1)
				kill(server_pid, 12);
			else
				kill(server_pid, 10);
			usleep(500);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int		pid;

	if (argc != 3)
	{
		write(2, "Fail: ./client <pid> <message>\n", 31);
		return (0);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		write(1, "invalid pid\n", 12);
		exit(1);
	}
	get_bit(argv[2], pid);
	return (0);
}
/*kill -l yaparak tüm unıx sinyalleri görebilirsin.Numaralarını yazarak sinyalleri uygulayabilirsin
 ubuntuda bu yok bunun yerine man 7 signal yapabilirsin*/
