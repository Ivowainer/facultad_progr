data Color = R | B
data RBT a = E | T Color (RBT a) a (RBT a)

lbalance :: Color -> (RBT a) -> a ->(RBT a) -> (RBT a)
lbalance B (T R (T R a x b) y c) z d = T R (T B a x b) y (T B c z d)
lbalance B (T R a x (T R b y c)) z d = T R (T B a x b) y (T B c z d)
lbalance c l a r = T c l a r

rbalance :: Color -> (RBT a) -> a -> (RBT a) -> (RBT a)
rbalance B a x (T R b y (T R c z d)) = T R (T B a x b) y (T B c z d)
rbalance B a x (T R (T R b y c) z d) = T R (T B a x b) y (T B c z d)
rbalance c l a r = T c l a r

insertarRBT :: Ord a => (RBT a) -> a -> (RBT a)
insertarRBT t x = makeBlack (ins t x)
    where
        ins E x = T R E x E
        ins (T c l a r) x
            | x > a             = rbalance c l a (ins r x)
            | x < a             = lbalance c (ins l x) a r
            | otherwise         = T c l a r
        makeBlack E = E
        makeBlack (T _ l a r) = T B l a r

{- ===== 5 ===== -}
data Tree123 a = Leaf | T2 a (Tree123 a) (Tree123 a) 
                      | T3 a a (Tree123 a) (Tree123 a) (Tree123 a)
                      | T4 a a a (Tree123 a) (Tree123 a) (Tree123 a) (Tree123 a)

rbTo123 :: Ord a => RBT a -> Tree123 a
rbTo123 E = Leaf
rbTo123 (T B (T R a x b) y (T R c z d)) = T4 x y z (rbTo123 a) (rbTo123 b) (rbTo123 c) (rbTo123 d)
rbTo123 (T B (T R a x b) y c) = T3 x y (rbTo123 a) (rbTo123 b) (rbTo123 c)
rbTo123 (T B c y (T R a x b)) = T3 x y (rbTo123 a) (rbTo123 b) (rbTo123 c)
rbTo123 (T B a x b) = T2 x (rbTo123 a) (rbTo123 b)
