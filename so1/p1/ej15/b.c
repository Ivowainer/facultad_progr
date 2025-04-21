#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#include <pthread.h>
#include <sys/epoll.h>

#define MAX_EVENTS 10

/*
 * Para probar, usar netcat. Ej:
 *
 *      $ nc localhost 4040
 *      NUEVO
 *      0
 *      NUEVO
 *      1
 *      CHAU
 */

void quit(char *s)
{
    perror(s);
    abort();
}

struct epoll_event ev, events[MAX_EVENTS];
pthread_t hilos[MAX_EVENTS];
int epollfd, cant_escuchados;

pthread_mutex_t mutex;

int U = 0;

int fd_readline(int fd, char *buf)
{
    int rc;
    int i = 0;

    while ((rc = read(fd, buf + i, 1)) > 0)
    {
        if (buf[i] == '\n')
            break;
        i++;
    }

    if (rc < 0)
        return rc;

    buf[i] = 0;
    return i;
}

void handle_conn(int csock)
{
    char buf[200];
    int rc;

    while (1)
    {
        /* Atendemos pedidos, uno por linea */
        rc = fd_readline(csock, buf);
        if (rc < 0)
            quit("read... raro");

        if (rc == 0)
        {
            /* linea vacia, se cerró la conexión */
            close(csock);
            return;
        }

        if (!strcmp(buf, "NUEVO"))
        {
            char reply[20];
            sprintf(reply, "%d\n", U);
            pthread_mutex_lock(&mutex);
            U++;
            pthread_mutex_unlock(&mutex);
            write(csock, reply, strlen(reply));
        }
        else if (!strcmp(buf, "CHAU"))
        {
            close(csock);
            return;
        }
    }
}

void *wait_for_clients(void *lsock)
{
    int csock;

    csock = accept(*(int *)lsock, NULL, NULL);

    if (csock < 0)
        quit("accept");

    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd = csock;

    epoll_ctl(epollfd, EPOLL_CTL_ADD, csock, &ev);

    handle_conn(csock);

    return NULL;
}

/* Crea un socket de escucha en puerto 4040 TCP */
int mk_lsock()
{
    struct sockaddr_in sa;
    int lsock;
    int rc;
    int yes = 1;

    /* Crear socket */
    lsock = socket(AF_INET, SOCK_STREAM, 0);
    if (lsock < 0)
        quit("socket");

    /* Setear opción reuseaddr... normalmente no es necesario */
    if (setsockopt(lsock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) == 1)
        quit("setsockopt");

    sa.sin_family = AF_INET;
    sa.sin_port = htons(4040);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

    /* Bindear al puerto 4040 TCP, en todas las direcciones disponibles */
    rc = bind(lsock, (struct sockaddr *)&sa, sizeof sa);
    if (rc < 0)
        quit("bind");

    /* Setear en modo escucha */
    rc = listen(lsock, 10);
    if (rc < 0)
        quit("listen");

    return lsock;
}

/*
    PASOS en MAIN:
    1. Creamos una instancia de epoll
    2. Crear evento y eventos
    3. epoll_ctrl (vigilar al lsock)
    4. epoll_wait (esperar eventos)
    5. controlar eventos

    PASOS en WAIT_F_CL:
    1. cambiar el ev.events a EPOLLIN | EPOLLET
    2. cambiar el fd del evento general al actual (client socket)
    3. modificar el epollfd para csock
*/
int main()
{
    int lsock;
    lsock = mk_lsock();

    epollfd = epoll_create1(0);

    ev.events = EPOLLIN;
    ev.data.fd = lsock;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, lsock, &ev);

    while (1)
    {
        cant_escuchados = epoll_wait(epollfd, events, MAX_EVENTS, -1);
        for (int i = 0; i < cant_escuchados; i++)
        {
            if (events[i].data.fd == lsock)
            {
                pthread_create(&hilos[i], NULL, wait_for_clients, &lsock);
            }
        }
    }
}