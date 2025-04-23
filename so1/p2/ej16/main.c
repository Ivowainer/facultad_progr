#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <signal.h>

#include "./hash/hash.h"

#define PORT 8080
#define MAX_EVENTS 10
#define CAPACITY 100
#define MSG_REQ_ERROR "EINVAL"

HashTable table;
struct epoll_event ev, events[MAX_EVENTS];
int nfds, lsock, epollfd;

void signal_handler(int signum)
{
    printf("ERROR!");
    close(lsock);
}

void quit(char *err)
{
    printf("ERROR: %s\n", err);
    exit(-1);
}

void msock()
{
    struct sockaddr_in s;
    s.sin_addr.s_addr = htonl(INADDR_ANY);
    s.sin_port = htons(PORT);
    s.sin_family = AF_INET;

    lsock = socket(AF_INET, SOCK_STREAM, 0);

    if (bind(lsock, (struct sockaddr *)&s, sizeof(s)) < 0)
        quit("bind");

    if (listen(lsock, 10) < 0)
        quit("en listen");
}

char **manage_string(int csock)
{
    char req[100];
    char *method = malloc(sizeof(char) * 4);
    char *key = malloc(sizeof(char) * 10);
    char *value = malloc(sizeof(char) * 10);
    char **method_key_val = malloc(sizeof(char *) * 3);

    /* MANAGE REQUEST STRING */
    char c;
    int i = 0;
    while (read(csock, &c, 1) > 0 && c != '\n')
        req[i++] = c;
    req[i] = '\0';

    /* SEPARATE METHOD/KEY/VALUE */
    // method
    for (i = 0; req[i] != ' ' && req[i] != '\0'; i++)
        method[i] = req[i];
    method[i] = '\0';
    // if Ctrl+c client side
    if (method[0] == '\0')
        return NULL;

    if (strcmp(method, "GET") && strcmp(method, "PUT") && strcmp(method, "DEL"))
    {
        send(csock, "EINVAL", strlen("EINVAL"), 0);
        send(csock, "\n", 1, 0);
        return NULL;
    }

    // key
    if (req[i] == '\0')
    {
        send(csock, "EINVAL", strlen("EINVAL"), 0);
        send(csock, "\n", 1, 0);
        return NULL;
    }
    i++; // <-- sumamos uno, porque está parado actualmente en el ' '
    int j;
    for (j = 0; req[i] != ' ' && req[i] != '\0'; i++, j++)
        key[j] = req[i];
    key[j] = '\0';

    // value
    if (strcmp(method, "PUT") == 0)
    {
        i++; // <-- sumamos uno, porque está parado actualmente en el ' '
        for (j = 0; req[i] != ' ' && req[i] != '\0'; i++, j++)
            value[j] = req[i];
        value[j] = '\0';
    }

    method_key_val[0] = method;
    method_key_val[1] = key;
    method_key_val[2] = value;

    return method_key_val;
}

void handle_conn(int csock)
{
    char **method_key_value = manage_string(csock);
    if (method_key_value == NULL)
        return;

    char *method = method_key_value[0];
    char *key = method_key_value[1];
    char *value = method_key_value[2];

    /* printf("METHOD: %s, KEY: %s, VALUE: %s\n", method, key, value); */
    if (strcmp(method, "GET") == 0)
    {
        void *as = hashtable_search(table, key);
        if (as == NULL)
        {
            send(csock, "NOT FOUND\n", strlen("NOT FOUND"), 0);
            send(csock, "\n", 1, 0);
            return;
        }

        send(csock, as, strlen(as), 0);
        send(csock, "\n", 1, 0);
    }
    else if (strcmp(method, "PUT") == 0)
        hashtable_insert(table, key, value);
}

int main()
{

    table = hashtable_create(CAPACITY, copy, comp, destr, simple_hash);
    msock();

    epollfd = epoll_create1(0);
    if (epollfd < 0)
        quit("epoll");

    ev.events = EPOLLIN;
    ev.data.fd = lsock;

    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, lsock, &ev) < 0)
        quit("epoll_ctl lsock");

    while (1)
    {
        nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
        if (nfds < 0)
            quit("epoll_wait");

        for (int n = 0; n < nfds; n++)
        {
            if (events[n].data.fd == lsock)
            {
                int csock = accept(lsock, NULL, NULL);
                if (csock < 0)
                    quit("accept");
                ev.data.fd = csock;
                ev.events = EPOLLIN | EPOLLET;
                if (epoll_ctl(epollfd, EPOLL_CTL_ADD, csock, &ev) < 0)
                    quit("epoll_ctl csock");
            }
            else
                handle_conn(events[n].data.fd);
        }
    }

    return 0;
}