#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>
#include "headers.h"

int main(){
    char buff[MAX_MSG+1];
    char msg[30]="hola ivo uwu";
    struct sockaddr_un cli_name, sv_name;

    cli_name.sun_family = AF_UNIX;
    strcpy(cli_name.sun_path, CLI_NAME);

    sv_name.sun_family = AF_UNIX;
    strcpy(sv_name.sun_path, SV_NAME);

    unlink(CLI_NAME);

    int cli_sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if(cli_sock < 0){
        printf("No me pude conectar");
        exit(-1);
    }

    connect(cli_sock, (struct sockaddr *)&sv_name, sizeof(struct sockaddr_un));

    /* char buff[1024];
    recv(cli_sock, buff, 1024, 0);
    printf("%s\n", buff); */



    printf("[CLI] Sending msg...\n");
    send(cli_sock, msg, strlen(msg)+1, 0);
    printf("[CLI] Sent \"%s\" to server\n", msg);
    recv(cli_sock, buff, MAX_MSG, 0);
    printf("[CLI] received \"%s\" from server\n", buff);
    return 0;
}