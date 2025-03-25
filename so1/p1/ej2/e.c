#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main(){
    __pid_t pid = fork();

    if(pid != 0){
        sleep(10);
        //while (1);
        wait(NULL);

    }
    return 0;
}