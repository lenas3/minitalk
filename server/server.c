#include <signal.h>
#include <unistd.h>
#include "ft_printf.h"


void get_char(int signal)
{
    char c;
    int i;

    i = 0;
    c = 0;
    while(i <= 7)
    {
        if(signal == SIGUSR1)
            c |=  1 << i;
        else if(signal == SIGUSR2)
            c |= 0 << i;
        i++;
    }
}

void catch_signal(int signal)
{
    //bu fonksiyonun tüm mesajı yazdırması gerek.
}

int main()
{
    pid_t pid;

    pid = getpid();
    ft_printf("Server PID = %d\n", pid);
    //subject'te server pid en basta yazsirilsin diyo.
    signal(SIGUSR1, catch_signal);
    signal(SIGUSR2, catch_signal);

}