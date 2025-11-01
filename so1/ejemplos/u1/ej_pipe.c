#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    int fd[2];
    pipe(fd);
    char msg[10] = "hola";

    __pid_t pid = fork();

    // el hijo lee, el padre escribe;
    if(pid == 0){
        char buffer;
        printf("Corriendo hijo...\n");
        close(fd[1]);

        char printbuffer[10];
        int readchar = 1;
        int i = 0;
        while(readchar == 1){
            readchar = read(fd[0], &buffer, 1);
            printbuffer[i++]=buffer;
        }

        printbuffer[i-1] = '\0';
        printf("%s\n", printbuffer);
        close(fd[0]);
    }else {
        close(fd[0]); 
        write(fd[1], msg, strlen(msg)); 
        close(fd[1]);
        wait(NULL);
    }
    return 0;
}