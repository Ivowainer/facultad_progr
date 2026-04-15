
module Lab02 where

{-
   Laboratorio 2
   EDyAII 2022
-}

import Data.List

-- 1) Dada la siguiente definición para representar árboles binarios:

data BTree a = E | Leaf a | Node (BTree a) (BTree a)

-- Definir las siguientes funciones:

-- a) altura, devuelve la altura de un árbol binario.

altura :: BTree a -> Int
altura = undefined

-- b) perfecto, determina si un árbol binario es perfecto (un árbol binario es perfecto si cada nodo tiene 0 o 2 hijos
-- y todas las hojas están a la misma distancia desde la raı́z).

perfecto :: BTree a -> Bool
perfecto= undefined

-- c) inorder, dado un árbol binario, construye una lista con el recorrido inorder del mismo.

inorder :: BTree a -> [a]
inorder = undefined 


-- 2) Dada las siguientes representaciones de árboles generales y de árboles binarios (con información en los nodos):

data GTree a = EG | NodeG a [GTree a]

data BinTree a = EB | NodeB (BinTree a) a (BinTree a)

{- Definir una función g2bt que dado un árbol nos devuelva un árbol binario de la siguiente manera:
   la función g2bt reemplaza cada nodo n del árbol general (NodeG) por un nodo n' del árbol binario (NodeB ), donde
   el hijo izquierdo de n' representa el hijo más izquierdo de n, y el hijo derecho de n' representa al hermano derecho
   de n, si existiese (observar que de esta forma, el hijo derecho de la raı́z es siempre vacı́o).
   
   
   Por ejemplo, sea t: 
       
                    A 
                 / | | \
                B  C D  E
               /|\     / \
              F G H   I   J
             /\       |
            K  L      M    
   
   g2bt t =
         
                  A
                 / 
                B 
               / \
              F   C 
             / \   \
            K   G   D
             \   \   \
              L   H   E
                     /
                    I
                   / \
                  M   J  
-}

g2bt :: GTree a -> BinTree a
g2bt = undefined


-- 3) Utilizando el tipo de árboles binarios definido en el ejercicio anterior, definir las siguientes funciones: 
{-
   a) dcn, que dado un árbol devuelva la lista de los elementos que se encuentran en el nivel más profundo 
      que contenga la máxima cantidad de elementos posibles. Por ejemplo, sea t:
            1
          /   \
         2     3
          \   / \
           4 5   6
                             
      dcn t = [2, 3], ya que en el primer nivel hay un elemento, en el segundo 2 siendo este número la máxima
      cantidad de elementos posibles para este nivel y en el nivel tercer hay 3 elementos siendo la cantidad máxima 4.
   -}

b1 :: BinTree Int
b1 = (NodeB (NodeB EB 6 EB) 1 (NodeB (NodeB EB 3 EB) 2 (NodeB EB 4 (NodeB EB 5 EB))))

b2 :: BinTree Int
b2 = (NodeB (NodeB (NodeB EB 7 EB) 6 (NodeB EB 8 EB)) 1 (NodeB (NodeB EB 3 EB) 2 (NodeB EB 4 (NodeB EB 5 EB))))

listOfListPerLevelAux :: BinTree a -> Int -> [a]
listOfListPerLevelAux EB _ = []
listOfListPerLevelAux (NodeB l a r) 1 = [a]
listOfListPerLevelAux (NodeB l a r) level = listOfListPerLevelAux l (level - 1) ++ listOfListPerLevelAux r (level - 1) 

{- Analicemos dos propiedades:
   - Si ningún nivel tiene la longitud de la potencia n-esima de 2, entonces siempre será la raíz del arbol (caso base)
   - La longitud de mayor longitud siempre será de abajo para arriba, pues, si encontramos una lista que cumple con esta propiedad en el nivel más bajo posible, no habrá otra lista de longitud mayor en niveles más altos

   PROBLEMA (PREGUNTAR): Para recorrer el arbol debo pasarle la profundiad (osea, debo calcular y recorrer el arbol), luego debo recorrerlo nuevamente para generar lista por cada nivel bajo

   idea: crear una lista de listas con cada nivel, osea: [[7], [5, 6], [1, 2, 3, 4]] (donde la posición indica el nivel, entonces al comparar la n-esima potencia de 2 (siendo n la posición) con la longitud de la lista, será menos costoso)
-}
{- Va recorriendo de arriba hacia abajo, comparando la longitud de la lista dada con la potencia n-esima de 2 (siendo n el nivel actual), se va quedando las que matchea igual -}
dcnAux :: BinTree a -> Int -> [a]
dncAux (NodeB l a r) 1 = [a]
dcnAux (NodeB l a r) level = 
   let 
      list = listOfListPerLevelAux (NodeB l a r) level
   in 
      if (length list) == 2^(level-1) then list else dcnAux (NodeB l a r) (level-1)

{- idea: crear una lista de listas con cada nivel, osea: [[7], [5, 6], [1, 2, 3, 4]] (donde la posición indica el nivel, entonces al comparar la n-esima potencia de 2 (siendo n la posición) con la longitud de la lista, será menos costoso) -}

idea1 :: BinTree a -> [[a]]
idea1 (NodeB EB a EB) = [a] : []
idea1 (NodeB l a r) = [[a]]

{- b) maxn, que dado un árbol devuelva la profundidad del nivel completo
      más profundo. Por ejemplo, maxn t = 2   -}

maxn :: BinTree a -> Int
maxn = undefined

{- c) podar, que elimine todas las ramas necesarias para transformar
      el árbol en un árbol completo con la máxima altura posible. 
      Por ejemplo,
         podar t = NodeB (NodeB EB 2 EB) 1 (NodeB EB 3 EB)
-}

podar :: BinTree a -> BinTree a
podar = undefined






