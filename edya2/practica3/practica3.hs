{--- ERJERCICIO 2 ---}
type Linea = (String, Int)

vacia  :: Linea
vacia = ("", 0)

moverIzq :: Linea -> Linea
moverIzq (str, 0) = (str, 0)
moverIzq (str, p) = (str, p-1)

moverDer :: Linea -> Linea
moverDer (str, p) = if p == (length str) - 1 then (str, p) else (str, p+1)

moverIni :: Linea -> Linea
moverIni (str, p) = (str, 0)

moverFin :: Linea -> Linea
moverFin (str, p) = (str, (length str) - 1)

insertar :: Char -> Linea -> Linea
insertar c (str, p) = (c : str, p+1)

{- BORRAR -}
borrarStr :: Linea -> String
borrarStr (c : str, 1) = str
borrarStr (c : str, p) = c : borrarStr (str, p-1)

borrar :: Linea -> Linea
borrar (str, p) = (borrarStr (str, p), p)

{--- ERJERCICIO 3 ---}
data CList a = EmptyCL | CUnit a | Consnoc a (CList a) a
    deriving(Show)

l1 :: CList Int 
l1 = Consnoc 1 (Consnoc 2 EmptyCL 3) 4

l2 :: CList Int
l2 = Consnoc 5 (Consnoc 6 EmptyCL 7) 8 

l3 :: CList Int
l3 = Consnoc 9 (Consnoc 10 (Consnoc 11 EmptyCL 12) 13) 14

l31 :: CList Int
l31 = Consnoc 9 (Consnoc 10 EmptyCL 11) 12
l32 :: CList Int
l32 = Consnoc 13 EmptyCL 14

listFList :: CList (CList Int)
listFList = snocCL (Consnoc l1 (CUnit l31) l32) (Consnoc 15 EmptyCL 16)

-- a
headCL :: CList a -> a
headCL EmptyCL = undefined
headCL (CUnit a) = a
headCL (Consnoc x _ y) = x

{- Auxiliar para agregar elemnto a la cola-}
snocCL :: CList a -> a -> CList a
snocCL EmptyCL z = CUnit z
snocCL (CUnit a) z = Consnoc a EmptyCL z
snocCL (Consnoc x xs y) z = Consnoc x (snocCL xs y) z

tailCL :: CList a -> CList a
tailCL EmptyCL = undefined
tailCL (CUnit _) = EmptyCL
tailCL (Consnoc _ list y) = snocCL list y 

isEmptyCL :: CList a -> Bool
isEmptyCL EmptyCL = True
isEmptyCL _ = False

isCUnit :: CList a -> Bool
isCUnit (CUnit _) = True
isCUnit _ = False

clistToList :: CList a -> [a]
clistToList EmptyCL = []
clistToList (CUnit x) = [x]
clistToList (Consnoc x xs y) = x : (clistToList xs ++ [y])

clistToListNested :: CList (CList a) -> [[a]]
clistToListNested = map clistToList . clistToList

-- b
reverseCL :: CList a -> CList a
reverseCL EmptyCL = EmptyCL
reverseCL (CUnit x) = CUnit x
reverseCL (Consnoc x list y) = Consnoc y (reverseCL list) x

{- Aux -}
snocHeadCL :: CList a -> a -> CList a
snocHeadCL EmptyCL x = CUnit x
snocHeadCL (CUnit a) x = Consnoc x EmptyCL a
snocHeadCL (Consnoc x list y) z = Consnoc z (snocHeadCL list x) y  

{- [1, 2, 3, 4] -> [1, 2, 3] -}
sacarTailCL :: CList a -> CList a
sacarTailCL EmptyCL = EmptyCL
sacarTailCL (CUnit a) = EmptyCL
sacarTailCL (Consnoc x list y) = snocHeadCL list x  


-- [[1], [1, 2], [1, 2, 3], [1, 2, 3, 4]]
-- c
inits :: CList a -> CList (CList a)
inits EmptyCL = EmptyCL
inits (CUnit x) = CUnit (CUnit x) -- [1] -> [[1]]
inits (Consnoc x list y) = snocCL (inits (sacarTailCL (Consnoc x list y))) (Consnoc x list y)   -- [1, 2, 3] -> [[1], [1, 2], [1, 2, 3]]

-- d
lasts :: CList a -> CList (CList a)
lasts cl = inits (reverseCL cl)

-- [[1, 2, 3], [4, 5], [6, 7]] -> [1, 2, 3, 4, 5, 6, 7]
-- e
appendCL :: CList a -> CList a -> CList a
appendCL cl EmptyCL = cl
appendCL cl (CUnit a) = snocCL cl a
appendCL cl (Consnoc x list y) = appendCL (snocCL cl x) (snocCL list y) -- [1, 2, 3], [4, 5, 6] -> [1, 2, 3, 4], [5, 6]

concatCL :: CList (CList a) -> CList a
concatCL (Consnoc x EmptyCL y) = appendCL x y
concatCL (Consnoc x (CUnit a) y) = appendCL (appendCL x a) y -- [[1, 2], [3, 4], [8, 9]] -> [[1, 2, 3, 4], [8, 9]]
concatCL (Consnoc x (Consnoc a list b) y) = concatCL (Consnoc (appendCL x a) EmptyCL (appendCL b y))

{- 4 -}
data Exp = Lit Int | Add Exp Exp | Sub Exp Exp | Prod Exp Exp | Div Exp Exp
eval :: Exp -> Int
eval (Lit a) = a
eval (Add x y) = (eval x) + (eval y)
eval (Sub x y) = (eval x) - (eval y)
eval (Prod x y) = (eval x) * (eval y)
eval (Div x y) = floor ((eval x) / (eval y))