/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asay <asay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:48:30 by asay              #+#    #+#             */
/*   Updated: 2025/12/02 19:01:33 by asay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "minitalk_bonus.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	sum;
	int		sign;

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
		if (sign == 1 && sum > 2147483647)
			return (0);
		if (sign == -1 && sum > -2147483648)
			return (0);
		i++;
	}
	return (sign * sum);
}

int	pid_exists(pid_t pid)
{
	if (kill(pid, 0) == -1)
		return (0);
	return (1);
}
