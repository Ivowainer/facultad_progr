#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/mman.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <signal.h>

#define STRING_SIZE 20
#define PORT 4040
// 3942

int lsock;
void *mem;

void quit(char *error)
{
    close(lsock);
    perror(error);
    exit(-1);
}

void handler(int signum)
{
    quit("server cerrado corte tipo");
}

void check_req(int csock, char req[30])
{
    if (req == NULL)
    {
        send(csock, "EINVAL", sizeof("EINVAL"), 0);
        close(csock);
        return;
    }
}

void manage_req(int csock, char req[30])
{
    char method[5];
    char value[STRING_SIZE];

    // METHOD
    strtok(req, " ");
    check_req(csock, req);

    if (strcmp("GET", req) != 0 && strcmp("DEL", req) != 0 && strcmp("PUT", req) != 0)
    {
        send(csock, "EINVAL", sizeof("EINVAL"), 0);
        close(csock);
    }
    strcpy(method, req);

    // KEY
    req = strtok(NULL, " ");
    check_req(csock, req);
    int k = atoi(req);
    if (req[0] != '0' && k == 0)
    {
        req = NULL;
        check_req(csock, req);
        return;
    }
    k = (k * STRING_SIZE) - 1;

    // VALUE
    if (strcmp("PUT", method) == 0)
    {
        req = strtok(NULL, " ");
        check_req(csock, req);
        strcpy(value, req);
    }

    if (strcmp(method, "GET") == 0)
    {
        char send_str[30];
        sprintf(send_str, "KEY %d: %s\n", (k / STRING_SIZE) + 1, (char *)(mem + k));
        send(csock, send_str, strlen("KEY %d: %s\n"), 0);
        send(csock, "\n", 1, 0);
    }
    if (strcmp(method, "PUT") == 0)
        strcpy(mem + k, value);
}

void get_string(int csock)
{
    char a;
    int i = 0;

    char req[30];

    while (read(csock, &a, 1) > 0)
    {
        // PUT 2 hola\0
        // GET 2\0
        if (a == '\n')
            break;
        req[i++] = a;
    }
    req[i] = '\0';

    if (strlen(req) <= 1)
    {
        close(csock);
        return;
    }

    manage_req(csock, req);
    get_string(csock);
}

/*
PUT 2 hola
GET 2
    output: hola
PUT 3 colo
GET 34
*/

void wait_for_clients(int lsock)
{
    int csock = accept(lsock, NULL, NULL);
    if (csock < 0)
        quit("EROR CLIENTE ACEPTAR");
    else
    {
        printf("NUEVA CONEXIÓN\n");
        pid_t pid = fork();
        if (pid == 0)
        {
            get_string(csock);
            close(lsock);
        }
        else
        {
            close(csock);
            wait_for_clients(lsock);
        }
    }
}

int set_socket()
{
    struct sockaddr_in sa;
    sa.sin_port = htons(PORT);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);
    sa.sin_family = AF_INET;

    int lsock = socket(AF_INET, SOCK_STREAM, 0);

    if (bind(lsock, (struct sockaddr *)&sa, sizeof(sa)) < 0)
        quit("BIND");

    if (listen(lsock, 10) < 0)
        quit("LISTEN");

    return lsock;
}

int main()
{
    lsock = set_socket();

    signal(SIGINT, handler);
    signal(SIGSEGV, handler);

    mem = mmap(NULL, STRING_SIZE * 25, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    wait_for_clients(lsock);
    return 0;
}