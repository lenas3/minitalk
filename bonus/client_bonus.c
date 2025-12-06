/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asay <asay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:28:21 by asay              #+#    #+#             */
/*   Updated: 2025/12/02 18:58:24 by asay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include   "minitalk_bonus.h"

int	g_server_sig;

void	client_handler(int signal)
{
	if (signal == SIGUSR1)
	{
		g_server_sig = 1;
		write(1, "Signal Received\n", 16);
	}
}

void	handle_signal(char *msg, pid_t pid, int i, int j)
{
	g_server_sig = 0;
	if ((msg[i] >> j) & 1)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	if (g_server_sig == 0)
		pause();
}

void	send_server(char *msg, pid_t pid)
{
	int	i;
	int	j;

	i = 0;
	while (msg[i])
	{
		j = 7;
		while (j >= 0)
		{
			handle_signal(msg, pid, i, j);
			j--;
		}
		i++;
	}
	j = 7;
	while (j >= 0)
	{
		g_server_sig = 0;
		kill(pid, SIGUSR2);
		while (g_server_sig == 0)
			pause();
		j--;
	}
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	struct sigaction	sa;

	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		if (pid <= 0 || !pid_exists(pid))
		{
			write(1, "Invalid PID\n", 13);
			return (0);
		}
		sigemptyset(&sa.sa_mask);
		sa.sa_handler = client_handler;
		sa.sa_flags = 0;
		sigaction(SIGUSR1, &sa, NULL);
		send_server(argv[2], pid);
	}
	else
		write(1, "Wrong number of arguments\n", 26);
	return (0);
}
