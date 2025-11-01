#include "headers.h"

#define LISTEN 10

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

int U = 0;

void quit(char *s)
{
    perror(s);
    abort();
}

int fd_readline(int fd, char *buf)
{
    int rc;
    int i = 0;

    /*
     * Leemos de a un caracter (no muy eficiente...) hasta
     * completar una línea.
     */
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

void handle_conn(int csock, void *shmem)
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
            exit(0);
            return;
        }

        if (!strcmp(buf, "NUEVO"))
        {
            char reply[20];

            int num = atoi((char *)shmem);
            num++;
            sprintf(shmem, "%d\n", num);

            write(csock, shmem, strlen(shmem));
        }
        else if (!strcmp(buf, "CHAU"))
        {

            printf("CON. TERMINADA FD: %d\n", csock);
            close(csock);
            return;
        }
    }
}

void wait_for_clients(int lsock, void *shmem)
{
    int csock;

    /* Esperamos una conexión, no nos interesa de donde viene */
    csock = accept(lsock, NULL, NULL);
    if (csock < 0)
        quit("accept");
    else
    {
        printf("NUEVA CONEXIÓN\n");
        pid_t pid = fork();
        if (pid == 0)
        {
            handle_conn(csock, shmem);
            close(lsock);
        }
        else
        {
            close(csock);
            wait_for_clients(lsock, shmem);
        }
    }
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
    rc = listen(lsock, LISTEN);
    if (rc < 0)
        quit("listen");

    /* Crear area mapeada */

    return lsock;
}

int main()
{
    int lsock;
    lsock = mk_lsock();

    void *shmem = mmap(NULL, 128, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    /* Necesitariamos tantos hijos como conex. reciba el sv */
    wait_for_clients(lsock, shmem);

    munmap(shmem, 128);
}