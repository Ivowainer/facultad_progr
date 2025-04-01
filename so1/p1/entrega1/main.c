#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

void shuffle(int* arr, int len){
    for(int i=0;i<len*2;i++){
        int i1 = rand()%len;
        int i2 = rand()%len;
        int aux = arr[i1];
        arr[i1]=arr[i2];
        arr[i2]=aux;
    }

}

void print_arr(int *arr, int len){
    for(int i = 0; i < len; i++){
        if(i %3 == 0 && i>0) printf("\n");
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(int argc, char** argv){
    
    /* print_arr(arr, n); */
    int n = atoi(argv[1]);

    int pipefd[2];
    if(pipe(pipefd) < 0)
        exit(-1);

    __pid_t pid = fork();
    if(pid == 0){
        close(pipefd[0]);
        srand(time(NULL));

        int len = n+1;
        int arr[len];
        for(int i=0; i<n;i++)
            arr[i]=i+1;
        shuffle(arr,n);
        arr[n]=EOF;
        
        for(int i=0; i<len;i++){
            write(pipefd[1], arr+i, sizeof(int));
        } 
        close(pipefd[1]);
    } else {
        close(pipefd[1]);
        int buff;
        int arr[n];
        wait(NULL);
        
        int i = 0;
        while(buff != EOF){
            read(pipefd[0], &buff, sizeof(int));
            arr[i++] = buff;
        }
        print_arr(arr,n);
        close(pipefd[0]);
    }

}