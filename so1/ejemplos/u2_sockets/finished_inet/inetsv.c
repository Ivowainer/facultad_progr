#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "headers.h"

int main(){
    char buff[MAX_MSG+1];
    socklen_t sock_len;

    struct sockaddr_in cli_name, sv_name;
    struct in_addr addr;

    cli_name.sin_family = AF_INET;
    cli_name.sin_port = htons(PORT);
    cli_name.sin_addr.s_addr = htonl(INADDR_ANY);

    sv_name.sin_family = AF_INET;
    sv_name.sin_port = htons(PORT);
    sv_name.sin_addr.s_addr = htonl(INADDR_ANY);

    int sv_sock = socket(AF_INET, SOCK_STREAM, 0);

    bind(sv_sock, (struct sockaddr*) &sv_name, sizeof(sv_name));

    listen(sv_sock, 1);
    
    int cli_sock = accept(sv_sock, NULL, NULL);
    
    int nbytes = recv(cli_sock, buff, MAX_MSG,0);
    printf("[SRV] received \"%s\" from client\n", buff);

    send(cli_sock, buff, nbytes, 0);
    printf("[SRV] \"%s\" sent to client\n", buff);
    
    return 0;
}