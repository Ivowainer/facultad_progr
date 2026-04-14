import Data.Char
import Debug.Trace (trace)

{- 1 -}
--a) 
test :: Num a => a -> a
test x = x+2
-- b)
esMenor :: Ord a => a -> a -> Bool
esMenor y z = y < z
-- c)
eq :: Ord a => a -> a -> Bool
eq x y = x == y
-- d)
showVal :: Show a => a -> [Char]
showVal x = "Valor: " ++ show x

{- 2 -}
-- a)
suma5 :: Num a => a -> a
suma5 = (+5)
-- b)
menorCero :: (Num a, Ord a) => a->Bool
menorCero = (0<)
-- c)
concatA :: String ->String
concatA = ('a':)
-- d) 
concatE :: String -> String
concatE = (++"\n")
-- e) 
filterEqSeven :: (Num a, Ord a) => [a]->[a]
filterEqSeven = filter (==7)
-- f)
mapConcatOne :: Num a => [[a]] -> [[a]]
mapConcatOne = map (++[1])

{- 3 -}
-- a)
aplicar5 :: (Int -> Int) -> Int
aplicar5 f = f 5
-- b) 
sumarN :: Int -> (Int -> Int)
sumarN x = (+x)
-- c)
sumar1Antes :: (Int -> Int) -> (Int -> Int)
sumar1Antes f = \x -> f(x+1)
-- d)
eq0 :: Int -> Bool
eq0 x = x == 0
-- e)
verify :: Bool -> (Bool -> Bool)
verify x = (==x)
-- f)
ordinal :: (Int, Char) -> Bool
ordinal (n,c) = n == ord c
-- g)
sumaPar :: (Int, Int) -> Int
sumaPar (x,y) = x+y
-- h)
doblePar :: Int -> (Int, Int)
doblePar x = (x, 2*x)
-- i)
siempreFalse :: a -> Bool
siempreFalse _ = False
-- j)
identidad :: a -> a
identidad x = x

{- 5 -}
-- a)
{- f x = let (y, z) = (x, x) in y -}
f :: a -> a
f x = x

-- b)
{- greater (x, y) = if x>y then True else False -}
greater :: Ord a => (a, a) -> Bool
greater (x, y) = x > y

-- c)
{- f' (x , y) = let z = x + y in g (z , y) where g (a, b) = a - b -}
f' :: Num a => (a, a) -> a
f' (x,y) = (x+y) - y

{- 6 -}
-- a)
smallest :: Ord a => (a, a, a) -> a
smallest = \(x,y,z) ->
    if x <= y && x<=z then x
    else if y<=z && y <= z then y
    else z

-- b)
second :: a -> a
second = \x -> x

-- c)
andThen :: Bool -> Bool -> Bool
andThen = \x -> (\y -> if x then y else False)

-- d)
twice :: (a -> b) -> a -> b
twice = \f -> (\x -> f x)

-- e)
flip' :: (a -> a -> b) -> a -> a -> b
flip' = \f -> (\x -> (\y -> f y x))

-- f)
inc :: Num a => a -> a
inc = \x -> x+1

{- 7 -}
-- a)
iff :: Bool -> Bool -> Bool
iff x y = if x then not y else y

-- b)
alpha :: a -> a
alpha x = x

{- 9 -}
zip3' :: [a] -> [b] -> [c] -> [(a,b,c)]
zip3' [] ys zs = []
zip3' xs [] zs = []
zip3' xs ys [] = []
zip3' (x : xs) (y : ys) (z : zs) = (x, y, z) : zip3' xs ys zs

zip3'' :: [a] -> [b] -> [c] -> [(a, b, c)]
zip3'' xs ys zs = [(x, y, z) | (x, (y, z)) <- zip xs (zip ys zs)]

{- 12 -}
type NumBin = [Bool]

-- a)
xor :: Bool -> Bool -> Bool
xor a b 
    | a && b    = False
    | a || b    = True
    | otherwise     = False

-- Asumimos que la primera lista es menor que la segunda
adjustLength :: NumBin -> NumBin -> NumBin
adjustLength xs ys = xs ++ [False | x <- [1..(length ys) - (length xs)]]

sumBinAux :: NumBin -> NumBin -> Bool -> NumBin
sumBinAux [] [] True = [True]
sumBinAux [] [] False = []
sumBinAux (x : xs) (y : ys) b 
    | not x && not y && not b   = False : sumBinAux xs ys False -- 0 + 0 = 0 (c = 0)
    | (not x && not y && b) || (xor x y && not b)   = True : sumBinAux xs ys False -- 1 + 0 = 1 (c = 0) || 0 + 1 = 1 (c = 0) || -- 0 + 0 + c = 1 (c = 0)
    | (x && y && not b ) || (xor x y && b)  = False : sumBinAux xs ys True -- 1 + 0 + c = 0 (c=1) || 0 + 1 + c = 0 (c=1) || -- 1 + 1 = 0 (c=1)
    | x && y && b    = True : sumBinAux xs ys True -- 1 + 1 + c = 1 (c=1)

sumBin :: NumBin -> NumBin -> NumBin
sumBin xs ys 
    | length xs < length ys     = sumBinAux (adjustLength xs ys) ys False
    | length xs > length ys     = sumBinAux (adjustLength ys xs) xs False
    | length xs == length ys     = sumBinAux xs ys False

-- b)
multAux :: Bool -> Bool -> Bool
multAux x y 
    | (not x && not y) || (xor x y) = False
    | x && y    = True

multBin :: NumBin -> NumBin -> NumBin
multBin xs [True] = xs
multBin xs [False] = [False | x <- [1..length xs]]
multBin xs (y : ys) = sumBin [multAux x y | x <- xs] (False : multBin xs ys)
