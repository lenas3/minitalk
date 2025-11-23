/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asay <asay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 20:53:27 by asay              #+#    #+#             */
/*   Updated: 2025/11/23 20:53:37 by asay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

/*
1. argüman kontrol et.
2. server PID sini al.
2.a. PID <= 0 oalaamz!!!
4. her karakterin her bitini server a gonder.
*/
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
            if((msg[i] >> j) & 1)
            {
                kill(pid, SIGUSR1);
                usleep(100);
            }
            else
            {
                kill(pid, SIGUSR2);
                usleep(100); 
        //kill'den sonra usleep koymak, sistemin sinyalleri yakalaması icin izin vermek gibi.
        //daha sağlıklı sinyal yakalayabilmesi icin bir süre uyutuyoruz. yine de biraz daha detaylı araştır.
            }
            j--;
        }
        i++;
    }
    i = 0;
    while(i < 8)
    {
        kill(pid, SIGUSR2);
        i++;
    }
}

int main(int argc, char **argv)
{
    pid_t pid;

    if(argc == 3)
    {
        pid = ft_atoi(argv[1]);
        if(pid <= 0)
        {
            write(1, "Gecersiz PID\n", 14);
            return 0;
        }
        send_server(argv[2], pid);
    }
    else
        write(1, "Yanliş Sayida Argüman Girildi\n", 32);
    return 0;
}