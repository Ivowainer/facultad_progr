from random import randint

""" Funciones Auxiliares """


def encontrarMayor(l):
    best = l[0]

    for x in l:
        if x > best:
            best = x

    return best


def split(str):
    palabras = []
    palabraTemporal = ""

    str += " "
    for x in str:
        if x != " ":
            palabraTemporal += x.lower()
        else:
            palabras.append(palabraTemporal.lower())
            palabraTemporal = ""
    return palabras


def calcularPromedio(l):
    suma = 0

    for i in l:
        suma += i

    return suma / len(l)


def letrasSeparadas(str):
    letras = []
    for x in str:
        if not x in letras and x != " ":
            letras.append(x)
    return letras


# 1. a) b) c)
def ej1(l, n):
    cant_veces = []

    for x in range(0, len(l)):
        if l[x] == n:
            cant_veces.append(x)

    return (len(cant_veces), cant_veces[0], cant_veces)


# 2. a) b)
def ej2(l):
    maximo = (l[0], 0)

    for x in range(0, len(l)):
        if l[x] > maximo[1]:
            maximo = (l[x], x)

    return maximo


# 3
def ej3(l, n):
    half = len(l) // 2
    start = 0
    end = len(l) - 1

    while start <= end and l[half] != n:
        if l[half] < n:
            start = half + 1
        else:
            end = half - 1

        half = (start + end) // 2

    if half != len(l):
        l.insert(half + 1, n)
        return l

    return half


# 4
def ej4(l):
    diccionario = {}
    for x in l:
        if x[0] in diccionario:
            diccionario[x[0]] = diccionario[x[0]] + [x[1]]
        else:
            diccionario[x[0]] = [x[1]]

    return diccionario


# 5 a) b)
def ej5_a(str):
    str = str.split(" ")
    dicc = {}
    for word in str:
        if word in dicc:
            dicc[word] += 1
        else:
            dicc[word] = 1

    return dicc


def ej5_b(str):
    dicc = {}

    for letter in str:
        if letter in dicc:
            dicc[letter] += 1
        else:
            dicc[letter] = 1

    return dicc


# 6
def ej6(str="Hola comoo andas"):
    str = str.split(" ")
    dicc = {}
    for word in str:
        for letter in word:
            if letter in dicc and len(dicc[letter]) < len(word):
                dicc[letter] = word
            elif not (letter in dicc):
                dicc[letter] = word
    return dicc


# 7. a) b)
def ej7(dicc):
    mayorPromedio = list(dicc)[0]

    for alumno in dicc:
        if calcularPromedio(dicc[alumno]) > calcularPromedio(dicc[mayorPromedio]):
            mayorPromedio = alumno

    alumno = input("alumno: ")
    return (calcularPromedio(dicc[mayorPromedio]), mayorPromedio)


# 8
def ej8(str, dicc):
    str = str.split()
    newStr = []

    for word in str:
        if word in dicc:
            random = randint(0, len(dicc[word]) - 1)

            palabraSinonimo = dicc[word][random]
            newStr.append(palabraSinonimo)
        else:
            newStr.append(word)

    return " ".join(newStr)


# 9
def ej9(dicc1, dicc2):
    monto = 0
    for x in dicc1:
        monto += dicc1[x] * dicc2[x]

    return monto


# 10
def ej10(l):
    return set(l)


def ej11(str1, str2):
    # interseccion de ambas cadenas
    str1 = str1.lower()
    str2 = str2.lower()

    return set(str1) & set(str2)


def ej12(conj1, conj2):
    # diferencia simetrica
    # (A-B)U(B-A)

    return conj1 - conj2


def ej13(l):
    a = set()
    a.update(l[0 : len(l) - 1])

    mayor = encontrarMayor(l)

    for i in range(1, mayor):
        if not i in a:
            a.add(i)

    return a


def ej14(dicc):
    # interseccion entre las listas
    conj = set(dicc[list(dicc.keys())[0]])
    tempor = set()

    for name in dicc:
        tempor.update(dicc[name])
        conj = tempor & conj
        tempor = set()

    return conj
