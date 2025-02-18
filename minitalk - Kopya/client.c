/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdinc <mdinc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:58:42 by mdinc             #+#    #+#             */
/*   Updated: 2025/02/17 22:53:15 by mdinc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

static int	ft_atoi(char *s)
{
	int nbr = 0;
	int i = 0;
	
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1);
		nbr = nbr * 10 + (s[i] - '0');
		i++;
	}
	return (nbr);
}

void	send_bit(char *message, int server_pid)
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
			usleep(1000);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int		server_pid;

	if (argc != 3)
	{
		write(2, "Fail: ./client <server_pid> <message>\n", 38);
		return (0);
	}
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
	{
		write(1, "invalid pid\n", 12);
		exit(1);
	}
	send_bit(argv[2], server_pid);
	return (0);
}
/*kill -l yaparak tüm unıx sinyalleri görebilirsin.Numaralarını yazarak sinyalleri uygulayabilirsin*/
