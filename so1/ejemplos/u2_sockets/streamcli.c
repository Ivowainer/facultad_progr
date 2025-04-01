#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

#include <sys/un.h> // <=== Sockets de dominio UNIX (LOCAL)

#define CLI_NAME "./CLI_NAME"
#define SV_NAME "./SV_NAME"

// Stream -> TCP
int main()
{
    struct sockaddr_un cli_name, sv_name;

    // SET Unix CLI_NAME
    cli_name.sun_family = AF_LOCAL;
    strcpy(cli_name.sun_path, CLI_NAME);

    // SET Unix SV_NAME
    sv_name.sun_family = AF_LOCAL;
    strcpy(sv_name.sun_path, SV_NAME);

    unlink(cli_name.sun_path); // ...

    int cli_sock = socket(AF_LOCAL, SOCK_STREAM, 0); // 0 para el default protocol, <== returns FD
    if (cli_sock < 0)
        exit(-1);

    int connect_result = connect(cli_sock, (struct sockaddr *)&sv_name, sizeof(struct sockaddr_un)); // fd, struct; recieve SOCKADDR (ch sockaddr_un --)
    if (connect_result < 0)
        exit(0);
    printf("[CLIENT STREAM] Socket conectado %d\n", connect_result);

    return 0;
}