#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

void handlerChild(int signum){
    printf("hijo\n");
    sleep(2);

    exit(0);
}

int main(){
    int status;
    __pid_t pid = fork();   

    if(pid == 0){
        struct sigaction sa;
        sa.sa_flags = SA_RESTART;
        sa.sa_handler = handlerChild;
        sigaction(SIGINT, &sa, NULL);

        while(1);
    
    } else {
        sleep(1);
        kill(pid, SIGINT);
        wait(&status);
        printf("padre\n");
    }
    return 0;
}