# Imprime los primeros 25 numeros naturales pares
# ej1 : Int -> None
# El parametro representa la cantidad de N numeros naturales pares
# entrada: 26, salida: 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26
def ej1(n):
    if n == 1:
        return

    if n % 2 == 0:
        print(n)

    ej1(n - 1)


# Imprime los primeros 100 numeros naturales pares
# ej2 : None -> None
# entrada: 26, salida: 2, 4, 6, 8, 10, 12, 14, 16... 100
def ej2():
    ej1(100)


# Imprime n numeros naturales pares luego de m
# ej3: Int Int -> None
# El primer parametro representa la cantidad de n numeros delante del segundo parametro (m)
# serán impresos, unicamente si estos son pares.
# entrada: 4 30, salida: 30, 32, 34
# entrada: 2 27, salida: 28
# entrada: 10 20, salida: 20, 22, 24, 26, 28, 30
def ej3(n, m):
    if n == 0:
        if m % 2 == 0:
            print(m)

        return

    if m % 2 == 0:
        print(m)

    ej3(n - 1, m + 1)


# Imprime los primeros n numeros naturales
# ej5: Int -> Int
# El parametro "n" representa la cantidad de n numeros que serán sumados
# entrada: 4 salida: 10
# entrada: 10 salida: 55
def ej5(n):
    if n == 0:
        return n

    return n + ej5(n - 1)


def ej6(n, m):
    if n >= m - 1:
        return 0

    return n + ej6(n + 1, m)


# Retorna str concatenado dos veces
# duplica: String -> String
# entrada: "Federico", salida: "FedericoFederico"
# entrada: "Hola", salida: "HolaHola"
def duplica(str):
    return str * 2


# Retorna str concatenado n veces
# duplica2: String Int -> String
# entrada: "Federico" 3, salida: "FedericoFedericoFederico"
# entrada: "Hola" 4, salida: "HolaHolaHolaHola"
def duplica2(str, n):
    return str * n


# Toma una opcion aritmetica elegida por el usuario y dos numeros con los que opera
# ej9: None -> None


def ej9():
    print("1. Suma")
    print("2. Resta")
    print("3. Multiplica")
    print("4. Divide")
    print("5. Salir")

    opcion = input("Elije una opción: ")

    if int(opcion) == 5:
        return

    if int(opcion) > 5 or int(opcion) < 1:
        print("---------------")
        print("Por favor, elije una opción valida")
        print("---------------")
        return ej9()

    n1 = input("Elije primer numero: ")
    n2 = input("Elije segundo numero: ")

    print(int(n2) + int(n1))

    if int(opcion) == 1:
        print("Suma: " + (n1 + n2))

    if int(opcion) == 2:
        print("Resta: " + (n1 - n2))

    if int(opcion) == 3:
        print("Multiplica: " + (n1 * n2))

    if int(opcion) == 4:
        print("Divide: " + (n1 / n2))


ej9()
