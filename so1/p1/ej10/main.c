#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
void handler(int signum){
    printf("HOLA! %d\n", getpid());
    //exit(-1);
}

int main() {
    pid_t pid = fork();
    if (pid < 0) exit(1);  // Error en el fork

    if (pid == 0) {  // Proceso hijo
        printf("Child: %d\n", getpid());
        
        // Configuración del manejador para SIGUSR1 en el hijo
        struct sigaction sa;
        sa.sa_handler = handler;
        sigemptyset(&sa.sa_mask);  // No bloquear señales mientras se maneja SIGUSR1
        sa.sa_flags = 0;
        sigaction(SIGUSR1, &sa, NULL);

        printf("Waiting signal from parent\n");
        
        // El hijo espera la señal del padre
        kill(getppid(), SIGUSR1);  // Enviar señal SIGUSR1 al padre
        printf("Sent SIGUSR1 to parent: %d\n", getppid());
        
        pause();  // El hijo espera una señal aquí
    } else {  // Proceso padre
        printf("Parent: %d\n", getpid());
        
        // Configuración del manejador para SIGUSR1 en el padre
        struct sigaction sa;
        sa.sa_handler = handler;
        sigemptyset(&sa.sa_mask);  // No bloquear señales mientras se maneja SIGUSR1
        sa.sa_flags = 0;
        sigaction(SIGUSR1, &sa, NULL);
        
        printf("Waiting signal from child\n");
        
        kill(pid, SIGUSR1);  // Enviar señal SIGUSR1 al hijo
        printf("Sent SIGUSR1 to child\n");
        
        pause();  // El padre espera la señal del hijo
        
        wait(NULL);  // Esperar a que el hijo termine
    }
    
    return 0;
}