/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psantos- <psantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 11:32:44 by psantos-          #+#    #+#             */
/*   Updated: 2025/06/09 11:16:03 by psantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

int	ft_atoi(const char *str)
{
	int	number;

	number = 0;
	while ((*str >= '0' && *str <= '9') && *str)
	{
		number = (number * 10) + (*str - '0');
		str++;
	}
	return (number);
}

void	send_char(pid_t server_pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if ((c >> i) & 1)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		usleep(100);
		i--;
	}
}

int	main(int argc, char *argv[])
{
	if (argc != 3)
		return (0);
	while (*argv[2])
		send_char((pid_t)ft_atoi(argv[1]), *argv[2]++);
	send_char((pid_t)ft_atoi(argv[1]), '\0');
	return (0);
}
