def ej1():
    for i in range(10, 21):
        print(i)


def ej2():
    for i in range(0, 7):
        for n in range(i, 7):
            print(i, n)


def factorial(n):
    result = 1
    for i in range(2, n + 1):
        result *= i
    return result


def ej4():
    m = input("Ingrese m: ")

    for i in range(0, int(m)):
        valor = input("Valor %i: ")
        result = factorial(int(valor))

        print(result)


def ej8():
    notas = []
    while True:
        nota = float(input("Ingrese una nota: "))

        notas.append(nota)

        print("----------------")
        print("¿Deseas introducir otra nota?")
        print("1. Si")
        print("2. Calcular promedio")
        print("----------------")

        option = int(input("Ingrese la opción: "))

        if option == 2:
            suma = 0

            for i in notas:
                suma += i

            promedio = suma / len(notas)

            print("->_>_>_>_>_>_>_>")
            print("El promedio de las notas ingresadas es:", promedio)
            print("->_>_>_>_>_>_>_>")
            break


def ej9():
    n1 = int(input("Ingrese el primer numero: "))
    n2 = int(input("Ingrese el segundo numero: "))

    if n2 > n1:
        return print("El segundo numero es mayor al primero")

    n3 = int(input("Ingrese el segundo numero nuevamente: "))

    if n2 != n3:
        return print("No son iguales")

    print(n1, n3)


def ej10(n1, n2):
    for i in range(1, n2):
        n1 *= i
        if n1 >= n2:
            return print("Hay " + str(i) + " multiplos de n1 que son menores que n2")


def ej11_a():
    contraseñaDefecto = "12345"

    contraseñaUsuario = input("Ingrese la contraseña: ")

    if contraseñaDefecto != contraseñaUsuario:
        print("-----------")
        print("La contraseña es incorrecta, por favor, intente nuevamente")
        print("-----------")
        return ej11_a()

    print("Ingresó correctamente")


def ej11_b(n1, n2, intentos):
    intentosAcumulados = 0
    for i in range(1, n2):
        intentosAcumulados += 1

        if intentos < intentosAcumulados:
            return print("Superaste la cantidad de intentos")

        n1 *= i

        if n1 >= n2:
            return print("Hay " + str(i) + " multiplos de n1 que son menores que n2")


def es_primo(n1):
    if n1 < 2:
        return print("No es primo")

    for i in range(2, n1):
        if n1 % i == 0:
            return print("No es primo")

    print("Es primo")
