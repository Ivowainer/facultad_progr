def posicionesMultiplo(l, n):
    newList = []
    for x in range(0, len(l)):
        if x % n == 0:
            newList.append(l[x])
    return newList


def sumElementos(l):
    sum = l[0]
    newList = [sum]

    for x in range(1, len(l)):
        sum += l[x]
        newList.append(sum)

    return newList


def elimina(l):
    return l[1 : len(l) - 1]


def ordenada(l):
    valor = True
    i = 0
    while i < len(l) and valor:
        if i != len(l) - 1 and l[i] > l[i + 1]:
            valor = False
        i += 1
    return valor


def duplicado(l):
    valor = False
    i = 0
    while i < len(l) - 1 and not valor:
        j = i + 1
        while j < len(l) and not valor:
            if l[i] == l[j]:
                valor = True
            j += 1

        i += 1

    return valor


def eliminaDuplicados(l):
    l = sorted(l)
    arr = [l[len(l) - 1]]
    for x in range(0, len(l) - 1):
        if l[x] != l[x + 1]:
            arr.append(l[x])
    return arr


def cant_distintas(l):
    return len(eliminaDuplicados(l))


def busqueda_binaria(arr, n):
    start = 0
    end = len(arr) - 1
    half = len(arr) // 2

    while start <= end and arr[half] != n:
        half = (start + end) // 2

        if arr[half] > n:
            end = half - 1

        if arr[half] < n:
            start = half + 1

    return arr[half] == n


def str_reverse(str):
    for x in range(len(str) - 1, -1, -1):
        print(str[x])


def contar(str, n):
    cont = 0
    for x in str:
        if x == n:
            cont += 1
    return cont


def vocales(str):
    cont = 0
    vocales = ["a", "e", "i", "o", "u"]

    for x in str:
        for y in vocales:
            if x.lower() == y:
                cont += 1

    return cont


def cinco_palabras(str):
    str = str.split(" ")
    cont = 0
    for x in str:
        if len(x) >= 5:
            cont += 1

    return "Se ha encontrado " + str(cont) + " palabra(s) con más de 5 caracteres"
