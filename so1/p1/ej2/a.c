#include <stdio.h>
#include <unistd.h>

int main(){
    char buff[1024];
    close(1);
    printf("No se imprime");
    return 0;
}