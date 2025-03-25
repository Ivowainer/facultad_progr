#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(){
    int *a = malloc(1*1000*1000*1000);
    for(int i = 0; i<1*1000*1000*100;i++){
        a[i] = 320;
        //sleep(1);
    }
    while(1);
    return 0;
}