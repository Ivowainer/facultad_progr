#include <stdio.h>
#include <unistd.h>

int main(){
    int fd = dup(1);

    /* NO SE SUSTITUYE POR EL ORIGINAL close(1) => no printf */
    close(fd);
    printf("%d", fd);
    return 0;
}