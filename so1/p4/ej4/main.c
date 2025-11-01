#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int es_primo_secuencial(long a) {
    long i = 2;

    for (; (i <= sqrt(a)) && (a % i != 0); i++);

    if (i >= sqrt(a)) {
        printf("Divisor: %ld\n", i);
        return 1;
    };

    return 0;
}

int es_primo_parallel(long a) {
    volatile int is_primo = 1;
    long limit = (long)sqrt(a);
#pragma omp parallel shared(is_primo)
    {
#pragma omp for
        for (long i = 2; i <= limit; i++) {
            if (!is_primo) continue;
            if (a % i == 0) {
                printf("Divisor: %ld\n", i);
#pragma omp critical
                {
                    is_primo = 0;
                }
            }
        };
    }

    return is_primo;
}

int main() {
    long N = 9223372036854775783;
    int result = es_primo_parallel(N);
    printf("Es primo: %d\n", result);

    return 0;
}
