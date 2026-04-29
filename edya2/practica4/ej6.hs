{- ===== 6 ===== -}
type Rank = Int
data Heap a = E | N Rank a (Heap a) (Heap a)

merge :: Ord a => Heap a -> Heap a -> Heap a
merge E h2 = h2
merge h1 E = h1
merge h1@(N _ x a1 b1) h2@(N _ y a2 b2) =
    if x<=y then makeH x a1 (merge b1 h2)
            else makeH y a2 (merge b2 h1)
    
rank :: Heap a -> Int
rank E = 0
rank (N r _ _ _) = r

makeH :: Ord a => a -> Heap a -> Heap a -> Heap a
makeH x a b = if rank a >= rank b then N (rank b + 1) x a b
                                  else N (rank a + 1) x b a

-- a)
fromList :: Ord a => [a] -> Heap a
fromList [] = E
fromList xs = foldr merge E (map (\x -> N 1 x E E) xs)