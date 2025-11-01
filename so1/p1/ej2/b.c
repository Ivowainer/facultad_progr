#include <stdio.h>
#include <unistd.h>

int main(){
    char buff[10];
    close(0);
    fgets(buff, 10, stdin);
    printf("ivo p+to");
    return 0;
}