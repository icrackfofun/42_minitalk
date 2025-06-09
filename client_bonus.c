/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psantos- <psantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 11:32:44 by psantos-          #+#    #+#             */
/*   Updated: 2025/06/09 11:33:00 by psantos-         ###   ########.fr       */
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

void	ack_handler(int sig)
{
	if (sig == SIGUSR2)
		write(1, "ACK\n", 4);
}

int	main(int argc, char *argv[])
{
	struct sigaction	sa;

	if (argc != 3)
		return (0);
	sa.sa_handler = ack_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR2, &sa, NULL);
	while (*argv[2])
		send_char((pid_t)ft_atoi(argv[1]), *argv[2]++);
	send_char((pid_t)ft_atoi(argv[1]), '\0');
	while (1)
		pause();
}
