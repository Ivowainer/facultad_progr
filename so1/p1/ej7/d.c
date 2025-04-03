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
        if (recv[strlen(recv) - 1] == '\n')
            recv[strlen(recv) - 1] = '\0'; // <-- Sacar el \n

        strcat(cmd, recv);

        // args
        int args_len = 1;
        args[0] = cmd;
        while (((recv = strtok(NULL, " ")) != 0) && (strcmp(&recv, '>') == 0) && (strcmp(&recv, '|') == 0))
            args[args_len++] = recv;

        args[args_len] = NULL;
        if (args_len > 1 && recv == NULL)
            args[args_len - 1][strlen(args[args_len - 1]) - 1] = '\0'; // <-- Sacar el \n del ultimo arg

        // args ">"
        int is_especial = recv == NULL ? 0 : 1;

        printf("LASCHAR: %s, IS_PIPE: %d, IS_MAJOR: %d\n", recv, *recv == '|', *recv == '>');

        return 0;

        int fd;
        if (is_especial == 1)
        {
            recv = strtok(NULL, " ");
            recv[strlen(recv) - 1] = '\0';
            fd = open(recv, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        }

        // exec commands
        pid_t pid = fork();
        if (pid == 0)
        {
            if (is_especial == 1)
            {
                dup2(fd, STDOUT_FILENO);
                close(fd);
            }

            int status_exec = execvp(cmd, args);

            if (status_exec == -1)
                exit(-1);
        }
        else
        {
            close(fd);
            wait(NULL);
        }
    }

    return 0;
}