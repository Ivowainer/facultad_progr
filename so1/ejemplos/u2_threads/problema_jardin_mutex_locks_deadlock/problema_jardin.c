/* 
    1. Mutex es un problema
    2. Se busca resolver race coindition limitando la region critica (donde se modifica algo de memoria compartida) para que acceda un unico proceso
    3. Se resuelve con LOCK
    

    Propiedad Safety
    Queremos que a lo sumo un proceso acceda a la seccion critica. Para eso se codeo un Lock
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
int visitante = 0;


// ++ NO ES ATOMICA
// Puede pasar que ambos hilos accedan al valor a la variable a la vez,
// y al intentar incrementarlo, incrementan el mismo valor
// con lo cual se pierde un incremento
// Hilo 1: lee visitante. visitante==10
// Hilo 2: lee visitante. visitante==10
// Hilo 1: incrementa visitante. visitante==11
// Hilo 2: incrementa visitante. visitante==11
// Valor final: visitante==11
void *molinete(void *ptr){
    for(int i=0; i<200000;i++){
        visitante++;
    }

    return ptr;
}

int main(){
    int v=0;
    pthread_t m1;
    pthread_t m2;

    pthread_create(&m1, NULL, molinete, &v);
    pthread_create(&m2, NULL, molinete, &v);

    pthread_join(m1,NULL);
    pthread_join(m2, NULL);

    printf("visitantes: %d\n", visitante);
    return 0;
}