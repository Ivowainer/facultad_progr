import random

preguntas = [
    "¿Cuál es la vida de un proceso?",
    "¿Qué es un cambio de contexto?",
    "¿Qué es un Sistema Operativo?",
    "¿Qué hace la llamada fork()?",
    "¿Qué es un pipe?",
    "¿Qué es un socket?",
    "¿Qué es la exclusión mutua?",
    "Explicá race condition, operación atómica y sección crítica.",
    "¿Qué es la propiedad de safety/liveness?",
    "¿Qué es un deadlock?",
    "¿Qué es un thread?",
    "¿Qué diferencias hay entre un proceso y un hilo?",
    "¿Qué mecanismos de sincronización conoces?",
    "¿Qué es busy waiting?",
    "¿Cómo funciona el algoritmo de Peterson?",
    "¿Cómo funciona el algoritmo de la Panadería de Lamport?",
    "¿Qué ventajas tiene usar threads sobre procesos?",
    "¿Que es la concurrencia y que diferencia tiene con el paralelismo?",
    "¿Que es Store Buffering?",
    "¿Que es Fence (Barrera de memoria)?",
    "¿Para que sirve volatile?",
    "Nombrar instrucciones de pthread mutex y para que sirven"
]

def timba_preguntas():
    random.shuffle(preguntas)

    while preguntas:
        input("")
        pregunta = preguntas.pop()
        print(pregunta)

    print("god")

if __name__ == "__main__":
    timba_preguntas()

