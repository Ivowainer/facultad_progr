#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main()
{
    char *cmd = malloc(sizeof(char) * 1024);

    while (1)
    {
        printf("> ");
        int status;

        fgets(cmd, 1024, stdin);
        cmd[strlen(cmd) - 1] = '\0'; // sin \n (salto de linea)
        pid_t pid = fork();

        if (strcmp(cmd, "exit") == 0)
            exit(0);

        if (pid == 0) // el hijo ejecutará el comando, mientras el padre espera
        {
            strtok(cmd, " ");
            char cmdAux[] = "/bin/";
            strcat(cmdAux, cmd);

            char *args[255];
            args[0] = cmdAux;
            int i = 1;
            while ((cmd = strtok(NULL, " ")))
                args[i++] = cmd;

            args[i] = NULL;

            if (execv(cmdAux, args) == -1)
                kill(getpid(), SIGKILL);
        }
        else
            wait(&status);
    }

    /* ==== liberar memoria ====*/
    return 0;
}