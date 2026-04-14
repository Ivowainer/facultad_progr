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

l1 :: CList Int 
l1 = Consnoc 1 (Consnoc 2 EmptyCL 3) 4

-- a
headCL :: CList a -> a
headCL EmptyCL = undefined
headCL (CUnit a) = a
headCL (Consnoc x _ y) = x

{- Auxiliar para agregar elemnto -}
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

-- b
reverseCL :: CList a -> CList a
reverseCL EmptyCL = EmptyCL
reverseCL (CUnit x) = CUnit x
reverseCL (Consnoc x list y) = Consnoc y (reverseCL list) x