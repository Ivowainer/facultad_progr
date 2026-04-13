-- 1) Dada la siguiente definición para representar árboles binarios:

data BTree a = E | Leaf a | Node (BTree a) (BTree a)


{- ARBOLES PARA TESTEAR -}
nbalancedTree :: BTree Int
nbalancedTree = Node (Node (Leaf 3) (Node  (Leaf 4) (Leaf 6))) (Leaf 5)

balancedTree :: BTree Int
balancedTree = Node (Leaf 1) (Leaf 2)

-- Definir las siguientes funciones:
-- a) altura, devuelve la altura de un árbol binario.

altura :: BTree a -> Int
altura E = 0
altura (Leaf a) = 0
altura (Node l r) = 1 + max (altura l) (altura r)

-- b) perfecto, determina si un árbol binario es perfecto (un árbol binario es perfecto si cada nodo tiene 0 o 2 hijos
-- y todas las hojas están a la misma distancia desde la raı́z).


perfecto :: BTree a -> Bool
perfecto (Node (Node ll lr) (Leaf r)) = False
perfecto (Node (Leaf l) (Node rl rr)) = False
perfecto (Node l r) = perfecto l && perfecto r && (altura l == altura r)
perfecto _ = True

-- c) inorder, dado un árbol binario, construye una lista con el recorrido inorder del mismo.

inorder :: BTree a -> [a]
inorder E = []
inorder (Leaf a) = [a]
inorder (Node l r) = inorder l ++ inorder r

-- 2) Dada las siguientes representaciones de árboles generales y de árboles binarios (con información en los nodos):

data GTree a = EG | NodeG a [GTree a]
data BinTree a = EB | NodeB (BinTree a) a (BinTree a)

{- ARBOLES DE PRUEBA -}
g1 :: GTree Char
g1 =
  NodeG 'A'
    [ NodeG 'B'
        [ NodeG 'F' [NodeG 'K' [], NodeG 'L' []]
        , NodeG 'G' []
        , NodeG 'H' []
        ]
    , NodeG 'C' []
    , NodeG 'D' []
    , NodeG 'E'
        [ NodeG 'I' [NodeG 'M' []]
        , NodeG 'J' []
        ]
    ]

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

{- AUX -}
inorderBin :: BinTree a -> [a]
inorderBin EB = []
inorderBin (NodeB EB a EB) = [a]
inorderBin (NodeB l a r) = [a] ++ inorderBin l ++ inorderBin r

g2bt :: GTree a -> BinTree a
g2bt EG = EB
g2bt (NodeG a hijos) = NodeB (brosADerecha hijos) a EB

brosADerecha :: [GTree a] -> BinTree a
brosADerecha [] = EB
brosADerecha (t:ts) =
  case g2bt t of
    EB -> brosADerecha ts
    NodeB l a _ -> NodeB l a (brosADerecha ts)

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
b1 = NodeB (NodeB EB 2 (NodeB EB 4 EB)) 1 (NodeB (NodeB EB 5 EB) 3 (NodeB EB 6 EB))

b2 :: BinTree Int
b2 = NodeB (NodeB (NodeB EB 1 EB) 5 (NodeB EB 2 EB)) 7 (NodeB (NodeB EB 3 EB) 6 (NodeB EB 4 EB))

{- AUX -}
alturaBin :: BinTree a -> Int
alturaBin EB = 0
alturaBin (NodeB l a r) = 1 + max (alturaBin l) (alturaBin r)

listPerLevel :: BinTree a -> Int -> [a]
listPerLevel EB _ = []
listPerLevel (NodeB l a r) 1 = [a]
listPerLevel (NodeB l a r) level = listPerLevel l (level-1) ++ listPerLevel r (level-1)

dcnAux :: BinTree a -> Int -> [a]
dcnAux (NodeB l a r) 1 = [a]
dcnAux (NodeB l a r) level =
   let
      list = listPerLevel (NodeB l a r) level
   in
      if length list == 2^(level-1) then list else dcnAux (NodeB l a r) (level-1)

{- Recorre:
      - n, para saber la altura
      - n * n, pues por cada altura que queremos la lista (listPerLevel) vamos recorriendo hasta la altura indicada los n nodos. Sería n * lg n si fuera un arbol balanceado, pero si es una lista, veamos que la altura es n. Por lo tanto, n² es el peor caso
-}

dcn :: BinTree a -> [a] 
dcn (NodeB l a r) = dcnAux (NodeB l a r) (alturaBin (NodeB l a r))

{- 
   Veamos su versión optimizada. La idea sería crear una lista de listas para, por ejemplo, el arbol
                       7
                     /   \
                    5     6
                   / \   / \
                  1  2  3  4
   de la forma [[7], [5,6], [1,2,3,4]]. Veamos que si iteramos la lista, 2^i (siendo i la posición actual) debe ser igual a la longitud del elemento actual, si esto se cumple, basta con ir agarrando los ultimos elementos de la lista.
   Una forma más optima, es hacerlo al revés, 2^(length lista - i - 1), a la primera que encuentre que es igual a la longitud del elemento, será esa la lista
-}
listAllLevels :: BinTree a -> [[a]]
listAllLevels EB = [[]]
listAllLevels (NodeB EB a EB) = [[a]]
listAllLevels (NodeB l a r) = [a] : map (uncurry (++)) (zip (listAllLevels l) (listAllLevels r))

dcnOptimizado :: BinTree a -> [a]
dcnOptimizado (NodeB l a r) = 
   let 
      altura = alturaBin (NodeB l a r)
      list = reverse (listAllLevels (NodeB l a r))
   in  dcnOptimizadoAux (zip list (reverse [0..(altura-1)]))
   where 
      dcnOptimizadoAux [] = []
      dcnOptimizadoAux ((x, i) : xs) = if 2^i == length x then x else dcnOptimizadoAux xs

{- b) maxn, que dado un árbol devuelva la profundidad del nivel completo
      más profundo. Por ejemplo, maxn t = 2   -}

maxn :: BinTree a -> Int
maxn (NodeB l a r) = 
   let
      altura = alturaBin (NodeB l a r)
      list = reverse (listAllLevels (NodeB l a r))
   in maxnAux (zip list (reverse [0..(altura-1)]))
   where 
      maxnAux [] = 0
      maxnAux ((x, i) : xs) = if 2^i == length x then i+1 else maxnAux xs

{- c) podar, que elimine todas las ramas necesarias para transformar
      el árbol en un árbol completo con la máxima altura posible. 
      Por ejemplo,
         podar t = NodeB (NodeB EB 2 EB) 1 (NodeB EB 3 EB)
-}

podarAux :: BinTree a -> Int -> BinTree a
podarAux (NodeB l a r) 1 = NodeB EB a EB
podarAux (NodeB l a r) level = NodeB (podarAux l (level-1)) a (podarAux r (level-1))

podar :: BinTree a -> BinTree a
podar (NodeB l a r) = podarAux (NodeB l a r) (maxn (NodeB l a r))

mostrarArbol :: Show a => BinTree a -> String
mostrarArbol t = unlines (dibujar "" True t)
  where
    dibujar pref esUltimo EB =
      [pref ++ (if esUltimo then "\\-- " else "+-- ") ++ "EB"]

    dibujar pref esUltimo (NodeB l x r) =
      [pref ++ (if esUltimo then "\\-- " else "+-- ") ++ show x]
      ++ dibujar (pref ++ (if esUltimo then "    " else "|   ")) False l
      ++ dibujar (pref ++ (if esUltimo then "    " else "|   ")) True r