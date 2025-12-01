#ifndef MINITALK_BONUS_H
#define MINITALK_BONUS_H

#include <signal.h>
#include <unistd.h>

int	ft_char(char c);
int	ft_nbr(int nb);
void catch_signal(int signal, siginfo_t *info, void *context);
int	ft_atoi(const char *str);
void handle_signal(char *msg, pid_t pid, int i, int j);
void send_server(char *msg, pid_t pid);

#endif