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

char **get_args(char *recv, char *cmd, int *is_pipe, int *is_file)
{
    char **args = malloc(sizeof(char) * MAX_ARGS);
    int args_len = 1;
    args[0] = cmd;
    while (((recv = strtok(NULL, " ")) != 0) && (*recv != '>') && (*recv != '|'))
        args[args_len++] = recv;

    args[args_len] = NULL;
    if (args_len > 1 && recv == NULL)
        args[args_len - 1][strlen(args[args_len - 1]) - 1] = '\0';

    if (recv != NULL)
    {
        *is_pipe = *recv == '|';
        *is_file = *recv == '>';
    }

    return args;
}

char *get_cmd(char *recv)
{
    char *cmd = malloc(sizeof(char) * 256);
    cmd[0] = '/';
    cmd[1] = 'b';
    cmd[2] = 'i';
    cmd[3] = 'n';
    cmd[4] = '/';

    strtok(recv, " ");

    if (recv[strlen(recv) - 1] == '\n')
        recv[strlen(recv) - 1] = '\0'; // <-- Sacar el \n

    strcat(cmd, recv);

    return cmd;
}

int main()
{

    while (1)
    {
        printf("> ");

        char *recv = malloc(sizeof(char) * 256);

        // main command
        fgets(recv, 256, stdin);
        char *cmd = get_cmd(recv);

        // args
        int is_pipe; // <-- Si is_pipe es 1, significa que el comando seguido puede tener más comandos incluso, se llama recursivamente
        int is_file; // <-- Si is_file es 1, significa que el comando seguido es un archivo a crear
        char **first_args = get_args(recv, cmd, &is_pipe, &is_file);

        // args ">"
        int fd;
        if (is_file == 1)
        {
            recv = strtok(NULL, " ");
            recv[strlen(recv) - 1] = '\0';
            fd = open(recv, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        }

        // exec commands
        pid_t pid = fork();
        if (pid == 0)
        {
            if (is_file == 1)
            {
                dup2(fd, STDOUT_FILENO);
                close(fd);
            }

            int status_exec = execvp(cmd, first_args);
            if (status_exec == -1)
                exit(-1);
        }
        else
        {
            wait(NULL);
            if (is_file == 1)
                close(fd);
        }
    }

    return 0;
}