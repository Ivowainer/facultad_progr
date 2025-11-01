#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include "headers.h"

int main(){
    char buff[MAX_MSG+1];
    socklen_t sock_len;

    struct sockaddr_un cli_name, sv_name;

    cli_name.sun_family = AF_UNIX;
    strcpy(cli_name.sun_path, CLI_NAME);

    sv_name.sun_family = AF_UNIX;
    strcpy(sv_name.sun_path, SV_NAME);

    unlink(SV_NAME);

    int sv_sock = socket(AF_UNIX, SOCK_STREAM, 0);

    bind(sv_sock, (struct sockaddr*) &sv_name, sizeof(sv_name));

    listen(sv_sock, 1);
    
    int cli_sock = accept(sv_sock, (struct sockaddr*) &cli_name, &sock_len);
    
    /* char msg[256] = "FULVIO";
    send(cli_sock, msg, strlen(msg), 0); */
    
    int nbytes = recv(cli_sock, buff, MAX_MSG,0);
    printf("[SRV] received \"%s\" from client\n", buff);

    send(cli_sock, buff, nbytes, 0);
    printf("[SRV] \"%s\" sent to client\n", buff);
    
    remove(SV_NAME);
    return 0;
}