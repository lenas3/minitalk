/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asay <asay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:33:31 by asay              #+#    #+#             */
/*   Updated: 2025/12/02 19:04:14 by asay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <signal.h>
# include <unistd.h>

typedef struct s_ctrl{
	int	server_pid;
}t_pid_ctrl;

int		ft_char(char c);
int		ft_nbr(int nb);
void	catch_signal(int signal, siginfo_t *info, void *context);
int		ft_atoi(const char *str);
void	handle_signal(char *msg, pid_t pid, int i, int j);
void	send_server(char *msg, pid_t pid);
int		pid_exists(pid_t pid);

#endif