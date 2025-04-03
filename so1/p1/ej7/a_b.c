#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MAX_ARGS 10

void print_args(char *args[MAX_ARGS])
{
    int i = 1;
    while (args[i] != NULL)
        printf("ARG[%d]: %s\n", i, args[i++]);
}

int main()
{

    while (1)
    {
        printf("> ");

        char cmd[256] = "/bin/";
        char *recv = malloc(sizeof(char) * 256);
        char *args[MAX_ARGS];

        // main command
        fgets(recv, 256, stdin);
        strtok(recv, " ");
        if (strcmp("\n", &recv[strlen(recv) - 1]) == 0)
            recv[strlen(recv) - 1] = '\0'; // <-- Sacar el \n

        strcat(cmd, recv);

        // args
        int args_len = 1;
        args[0] = cmd;
        while ((recv = strtok(NULL, " ")) != 0)
            args[args_len++] = recv;
        args[args_len] = NULL;
        if (args_len > 1)
            args[args_len - 1][strlen(args[args_len - 1]) - 1] = '\0'; // <-- Sacar el \n

        // exec commands
        pid_t pid = fork();
        if (pid == 0)
            execvp(cmd, args);
        else
            wait(NULL);
    }

    /* pid_t pid = fork(); */
    /* if (pid == 0)
    {
        execvp();
    }
    else
    {
        sleep(1); // <-- Se ejecutará el hijo primero
        wait(NULL);
    } */

    return 0;
}