{- ==== EJERCICIO 1 ==== -}

data Tree a = Empty | Nodo (Tree a) a (Tree a)

-- a)
completo :: a -> Int -> Tree a
completo x 0 = Empty
completo x d = Nodo t x t
    where t = completo x (d-1)

-- b)
balanceado :: a -> Int -> Tree a
balanceado x 0 = Empty
balanceado x d 
    | odd d             = Nodo t x t
    | otherwise         = Nodo t x t'
    where
        t  = balanceado x (div d 2)
        t' = balanceado x (div (d-1) 2)

{- ==== EJERCICIO 2 ==== -}

data BST a = Leaf | Node (BST a) a (BST a)

-- a)
maximum' :: Ord a => BST a -> a
maximum' (Node _ a Leaf) = a
maximum' (Node _ _ r) = maximum' r

minimum' :: Ord a => BST a -> a
minimum' (Node Leaf a _) = a
minimum' (Node l _ _) = minimum' l

-- b)
checkBST :: Ord a => BST a -> Bool
checkBST (Node Leaf b Leaf) = True
checkBST (Node l a Leaf) = a >= maximum' l && checkBST l
checkBST (Node Leaf a r) = a < minimum' r && checkBST r
checkBST (Node l a r) = a < minimum' r && a >= maximum' l && checkBST l && checkBST r

-- c)
splitBST :: Ord a => BST a -> a -> (BST a, BST a)
splitBST Leaf a = (Leaf, Leaf)
splitBST (Node l x r) a
    | a < x         = 
        let
            (l', r')  = splitBST l a
        in (l', Node r' x r)
    | a > x         =
        let
            (l', r') = splitBST r a
        in (Node l x l', r')
    | a == x        = (Node l x Leaf, r)

-- d)
join :: Ord a => BST a -> BST a -> BST a
join Leaf Leaf = Leaf
join Leaf t = t
join t Leaf = t
join t1 t2@(Node l2 y r2) =
    let (c, g) = splitBST t1 y
    in Node (join c l2) y (join g r2)

inorder :: Tree a -> [a]
inorder Empty = []
inorder (Nodo l a r) = inorder l ++ [a] ++ inorder r

