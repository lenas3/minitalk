/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asay <asay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:59:43 by asay              #+#    #+#             */
/*   Updated: 2025/11/23 19:59:43 by asay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_char(char c)
{
	int	value;

	value = write(1, &c, 1);
	return (value);
}

int	ft_nbr(int nb)
{
	int	i;

	i = 0;
	if (nb == -2147483648)
	{
		ft_char('-');
		write(1, "2147483648", 10);
		return (11);
	}
	if (nb < 0)
	{
		i = 1;
		ft_char('-');
		nb = -nb;
	}
	if (nb > 9)
	{
		i += ft_nbr(nb / 10);
	}
	ft_char('0' + nb % 10);
	i++;
	return (i);
}

void catch_signal(int signal, siginfo_t *info, void *context)
{
	static int  bit;
	static char letter;

	(void) context;
	letter <<= 1;
	if(signal == SIGUSR1)
		letter |= 1;
	else if(signal == SIGUSR2)
		letter |= 0;
	bit++;
	if(bit == 8)
	{
		write(1, &letter, 1);
		bit = 0;
		letter = 0;	
	}
	kill(info->si_pid, SIGUSR1);
}

int main()
{
	struct sigaction sigact;
	pid_t pid;

	sigact.sa_sigaction = catch_signal; 
	sigact.sa_flags = SA_SIGINFO;
	write(1, "Server PID: ", 12);
	pid = getpid();
	ft_nbr(pid);
	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);
	write(1, "\n", 1);
	while(1)
		pause();
	return (0);
}
