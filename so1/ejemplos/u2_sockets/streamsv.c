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
    char msg[256] = "Aa";

    struct sockaddr_un cli_name, sv_name;

    socklen_t cli_size;

    // SET Unix CLI_NAME
    cli_name.sun_family = AF_LOCAL;
    strcpy(cli_name.sun_path, CLI_NAME);

    // SET Unix SV_NAME
    sv_name.sun_family = AF_LOCAL;
    strcpy(sv_name.sun_path, SV_NAME);

    unlink(sv_name.sun_path); // ...

    int sv_sock = socket(AF_LOCAL, SOCK_STREAM, 0); // 0 para el default protocol, <== returns FD
    if (sv_sock < 0)
        exit(-1);

    bind(sv_sock, (struct sockaddr *)&sv_name, sizeof(sv_name)); // une extremos del socket cli
    listen(sv_sock, 5);                                          // cant clients q escucha en el socket sv

    int cli_sock = accept(sv_sock, (struct sockaddr *)&cli_name, &cli_size); // en q socket lo acepta, el archivo de comunicación (address) y el size de lo recibido

    send(cli_sock, msg, sizeof(msg), 0);

    close(sv_sock);

    return 0;
}
