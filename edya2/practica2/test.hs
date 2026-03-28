module Lab01 where

import Data.List
import Data.Char

{-
1) Corregir los siguientes programas de modo que sean aceptados por GHCi.
-}

-- a)
not2 :: Bool -> Bool
not2 b = case b of
  True -> False
  False -> True

-- b)
init2 :: [a] -> [a]
init2 [x] = []
init2 (x : xs) = x : init2 xs
init2 [] = error "empty list"

-- c)
length2 :: [a] -> Int
length2 [] = 0
length2 (_ : l) = 1 + length2 l

-- d)
list123 = 1 : 2 : 3 : []

-- e)
(++!) :: [a] -> [a] -> [a]
[] ++! ys = ys
(x : xs) ++! ys = x : xs ++! ys

-- f)
addToTail :: Int -> [Int] -> [Int]
addToTail x xs = map (+ x) (tail xs)

-- g)
listmin :: (Ord a) => [a] -> a
listmin xs = (head . sort) xs

-- h) (*)
smap :: (a -> a) -> [a] -> [a]
smap f [] = []
smap f [x] = [f x]
smap f (x : xs) = f x : smap f xs

{- 2. Definir las siguientes funciones y determinar su tipo: -}

-- a) five, que dado cualquier valor, devuelve 5
five :: a -> Int
five x = 5

-- b) apply, que toma una función y un valor, y devuelve el resultado de aplicar la función al valor dado
apply :: (a -> b) -> a -> b
apply f x = f x

-- c) ident, la función identidad
ident :: a -> a
ident x = x

-- d) first, que toma un par ordenado, y devuelve su primera componente
first :: (a, b) -> a
first (a, b) = a

-- e) derive, que aproxima la derivada de una función dada en un punto dado
derive :: (Fractional a) => (a -> a) -> a -> a
derive f x = (f (x + h) - f (x - h)) / (2 * h)
  where
    h = 0.0001

-- f) sign, la función signo
sign :: (Ord a, Num a) => a -> a
sign x
  | x == 0 = 0
  | x < 0 = -1
  | otherwise = 1

-- g) vabs, la función valor absoluto (usando sign y sin usarla)
vabs :: (Ord a, Num a) => a -> a
vabs x
  | x >= 0 = x
  | otherwise = (sign x) * x

-- h) pot, que toma un entero y un número, y devuelve el resultado de elevar el segundo a la potencia dada por el primero
pot :: Num a => Int -> a -> a
pot n x = x ^ n

-- i) xor, el operador de disyunción exclusiva
xor :: Bool -> Bool -> Bool
xor a b 
    | a && b    = True
    | not (a || b)    = True
    | otherwise     = False

-- j) max3, que toma tres números enteros y devuelve el máximo entre llos
max3 :: Int -> Int -> Int -> Int
max3 a b c = max c (max a b)

-- k) swap, que toma un par y devuelve el par con sus componentes invertidas
swap :: (a, b) -> (b, a)
swap (x, y) = (y, x)

{- 3) Definir una función que determine si un año es bisiesto o no, de acuerdo a la siguiente definición: -}

{- año bisiesto 1. m. El que tiene un día más que el año común, añadido al mes de febrero. Se repite
cada cuatro años, a excepción del último de cada siglo cuyo número de centenas no sea múltiplo
de cuatro. (Diccionario de la Real Academia Espaola, 22ª ed.)
Cuál es el tipo de la función definida? -}

bisiesto :: Int -> Bool
bisiesto y 
    | y `mod` 4 == 0    = True
    | otherwise     = False

{- 4)
Defina un operador infijo *$ que implemente la multiplicación de un
vector por un escalar. Representaremos a los vectores mediante listas
de Haskell. Así, dada una lista ns y un número n, el valor ns *$ n
debe ser igual a la lista ns con todos sus elementos multiplicados por
n. Por ejemplo,

[ 2, 3 ] *$ 5 == [ 10 , 15 ].

El operador *$ debe definirse de manera que la siguiente
expresión sea válida:

v = [1, 2, 3] *$ 2 *$ 4 -}
(*$) :: Num a => [a] -> a -> [a]
[] *$ n = []
(x : xs) *$ n = x * n : xs *$ n

{- 5) Definir las siguientes funciones usando listas por comprensión: -}

-- a) 'divisors', que dado un entero positivo 'x' devuelve la lista de los divisores de 'x' (o la lista vacía si el entero no es positivo)
divisors :: Int -> [Int]
divisors n = if n < 0 
    then [] 
    else [x | x <- [1..n], n `mod` x == 0]

-- b) 'matches', que dados un entero 'x' y una lista de enteros descarta de la lista los elementos distintos a 'x'
matches :: Int -> [Int] -> [Int]
{- matches n [] = []
matches n (x : xs) = if n == x then x : matches n xs else matches n xs -} {- No está mal, pero estoy un FC y hay q escribirlas por compresión -}
matches n xs = [x | x <- xs, x == n]

-- c) 'cuadrupla', que dado un entero 'n', devuelve todas las cuadruplas '(a,b,c,d)' que satisfacen a^2 + b^2 = c^2 + d^2, donde 0 <= a, b, c, d <= 'n'
cuadrupla :: Int -> [(Int, Int, Int, Int)]
cuadrupla n = [(a, b, c, d) | a <- [0..n], b <- [0..n], c <- [0..n], d <- [0..n], (a^2) + (b^2) == (c^2) + (d^2), a/=c && a/=d]
{- Agregué la última condición para que no me muestre los valores triviales -}

-- d) 'unique', que dada una lista 'xs' de enteros, devuelve la lista 'xs' sin elementos repetidos
unique :: [Int] -> [Int]
unique xs = [x | (x,i) <- zip xs [0..], not(elem x (take i xs))]

{- 6) El producto escalar de dos listas de enteros de igual longitud
es la suma de los productos de los elementos sucesivos (misma
posición) de ambas listas.  Definir una función 'scalarProduct' que
devuelva el producto escalar de dos listas.
Sugerencia: Usar las funciones 'zip' y 'sum'. -}

{- scalarProduct :: [Int] -> [Int] -> Int
scalarProduct [] [] = 0
scalarProduct (x : xs) (y : ys) = (x+y) + scalarProduct xs ys -}

scalarProduct :: [Int] -> [Int] -> Int
scalarProduct xs ys = sum [x+y | (x, i) <- zip xs [0..], (y, j) <- zip ys [0..], i==j]

{- 7) Definir mediante recursión explícita las siguientes funciones y escribir su tipo más general: -}

-- a) 'suma', que suma todos los elementos de una lista de números
suma :: Num a => [a] -> a
suma [] = 0
suma (x : xs) = x + suma xs

-- b) 'alguno', que devuelve True si algún elemento de una lista de valores booleanos es True, y False en caso contrario
alguno :: [Bool] -> Bool
alguno [] = False
alguno (x : xs) = if x then True else alguno xs

-- c) 'todos', que devuelve True si todos los elementos de una lista de valores booleanos son True, y False en caso contrario
todos :: [Bool] -> Bool
todos [] = True
todos (x : xs) = x && todos xs

-- d) 'codes', que dada una lista de caracteres, devuelve la lista de sus ordinales
{- Agregamos Data.Char -}
codes :: [Char] -> [Int]
codes [] = []
codes (x : xs) = ord x : codes xs

-- e) 'restos', que calcula la lista de los restos de la división de los elementos de una lista de números dada por otro número dado
restos :: Integral a => a -> [a] -> [a]
{- restos n xs = [x `mod` n | x <- xs] -} {- No usa recursión explicita)? -}
restos n [] = []
restos n (x : xs) = x `mod` n : restos n xs

-- f) 'cuadrados', que dada una lista de números, devuelva la lista de sus cuadrados
cuadrados :: Num a => [a] -> [a]
cuadrados [] = []
cuadrados (x : xs) = x^2 : cuadrados xs

-- g) 'longitudes', que dada una lista de listas, devuelve la lista de sus longitudes
longitudes :: [[a]] -> [Int]
longitudes [] = []
longitudes (x : xs) = length x : longitudes xs

-- h) 'orden', que dada una lista de pares de números, devuelve la lista de aquellos pares en los que la primera componente es menor que el triple de la segunda. (a,b) a < 3*b
orden :: (Ord a, Num a) => [(a, a)] -> [(a,a)]
orden [] = []
orden ((a,b) : xs) = if a<(3*b) then (a,b) : orden xs else orden xs

-- i) 'pares', que dada una lista de enteros, devuelve la lista de los elementos pares
pares :: [Int] -> [Int]
pares [] = []
pares (x : xs) = if x `mod` 2 == 0 then x : pares xs else pares xs

-- j) 'letras', que dada una lista de caracteres, devuelve la lista de aquellos que son letras (minúsculas o mayúsculas)
letras :: [Char] -> [Char]
letras [] = []
letras (c : cs) = if (ord c >= 97 && ord c <= 122) || (ord c >= 65 && ord c <= 90) then c : letras cs else letras cs

-- k) 'masDe', que dada una lista de listas 'xss' y un número 'n', devuelve la lista de aquellas listas de 'xss' con longitud mayor que 'n' 
masDe :: Int -> [[a]] -> [[a]]
masDe n [] = []
masDe n (xs : xss) = if length xs > n then xs : masDe n xss else masDe n xss