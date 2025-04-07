#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

pid_t otro_pid;

void sig_handler(int signum)
{
    printf("[PID %d]La senal llego\n", otro_pid);
    kill(otro_pid, SIGUSR1);
}

int main()
{
    pid_t pid = fork();
    signal(SIGUSR1, sig_handler);

    if (pid == 0)
    {
        printf("[HIJO] %d\n", getpid());
        sleep(1);
        otro_pid = getppid();
        while (1)
            ;
    }
    else
    {
        printf("[PADRE] %d\n", getpid());
        sleep(1);
        otro_pid = pid;
        raise(SIGUSR1);
        while (1)
            ;
    }
    return 0;
}