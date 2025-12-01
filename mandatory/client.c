/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asay <asay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 20:53:27 by asay              #+#    #+#             */
/*   Updated: 2025/11/30 20:36:16 by asay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include   "minitalk.h"

int server_sig;

int	ft_atoi(const char *str)
{
	int	i;
	int	sum;
	int	sign;

	i = 0;
	sum = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		sum = (sum * 10) + (str[i] - '0');
		i++;
	}
	return (sign * sum);
}

void client_handler(int signal)
{
    if (signal == SIGUSR1)
        server_sig = 1;
}

void handle_signal(char *msg, pid_t pid, int i, int j)
{
    server_sig = 0;
    if((msg[i] >> j) & 1)
        kill(pid, SIGUSR1);
    else
        kill(pid, SIGUSR2);
    if (server_sig == 0)
        pause();
}

void send_server(char *msg, pid_t pid)
{
    int i;
    int j;
    
    i = 0;
    while(msg[i])
    {
        j = 7;
        while(j >= 0)
        {
            handle_signal(msg, pid, i, j); // [TODO] rename function
            j--; 
        }
        i++;
    }
    j = 7;
    while (j >= 0)
    {
        server_sig = 0;
        kill(pid, SIGUSR2);
        while (server_sig == 0)
            pause();
        j--;
    }
}

int main(int argc, char **argv)
{
    pid_t pid;
    struct sigaction sa;

    if(argc == 3)
    {
        pid = ft_atoi(argv[1]);
        if(pid <= 0)
        {
            write(1, "Invalid PID\n", 13);
            return 0;
        }
        sigemptyset(&sa.sa_mask);
        sa.sa_handler = client_handler;
        sa.sa_flags = 0;
        sigaction(SIGUSR1, &sa, NULL);
        send_server(argv[2], pid);
    }
    else
        write(1, "Wrong number of arguments\n", 26);
    return 0;
}
