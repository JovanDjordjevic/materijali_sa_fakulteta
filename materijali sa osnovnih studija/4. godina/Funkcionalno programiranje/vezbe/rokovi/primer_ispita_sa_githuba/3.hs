module Zad3 where

-- Zadatak 3:

-- Definisati strukturu podataka `Stek a`, gde je `a`
-- proizvoljan tip. Stek moze biti prazan ili sadrzati
-- proizvoljan broj elemenata tipa `a`.

data Stek a = Empty
            | Val a (Stek a)
            deriving Eq

-- Kreirati funkcije `fromList` i `toList` koje konvertuju
-- [a] u `Stek a`, i `Stek a` u `[a]`, redom.

fromList :: [a] -> Stek a
fromList [] = Empty
fromList [x] = Val x Empty
fromList (x:xs) = Val x (fromList xs)

toList :: Stek a -> [a]
toList Empty = []
toList (Val a s) = a : (toList s)


-- Napisati QuickCheck test za funkcije `fromList` i `toList`.
prop_conversion :: (Eq a) => [a] -> Bool
prop_conversion lst = 
    lst == (toList $ fromList lst)

-- Instancirati Show nad `Stek a` (pretpostaviti da je
-- `a` u klasi Show) tako da se skup ispise u formatu:
--       < dno, ... , vrh >
-- (vrh i dno su elementi steka)
-- Za prazan stek:  </>

instance (Show a) => Show (Stek a) where
    show Empty = "</>"
    show a = "<" ++ show' a ++ ">"

show' :: (Show a) => Stek a -> String
show' Empty = ""
show' (Val a Empty) = show a
show' (Val a s) = (show' s) ++ ", " ++ (show a)

-- Instancirati Functor nad `Stek a`
instance Functor Stek where
    fmap f Empty = Empty
    fmap f (Val a s) = Val (f a) (fmap f s)







-- module Zad3 where

-- -- Zadatak 3:

-- -- Definisati strukturu podataka `Stek a`, gde je `a`
-- -- proizvoljan tip. Stek moze biti prazan ili sadrzati
-- -- proizvoljan broj elemenata tipa `a`.

-- data Stek a = Empty
--             | Top a (Stek a)
--             deriving Eq
-- -- Kreirati funkcije `fromList` i `toList` koje konvertuju
-- -- [a] u `Stek a`, i `Stek a` u `[a]`, redom.

-- fromList :: [a] -> Stek a
-- fromList [] = Empty
-- fromList [x] = Top x Empty
-- fromList (x:xs) = Top x (fromList xs)

-- toList :: Stek a -> [a]
-- toList Empty = []
-- toList (Top a s) = a : (toList s)


-- -- Napisati QuickCheck test za funkcije `fromList` i `toList`.
-- prop_conversion :: [Int] -> Bool
-- prop_conversion lst = lst == ( toList $ fromList lst)

-- -- Instancirati Show nad `Stek a` (pretpostaviti da je
-- -- `a` u klasi Show) tako da se skup ispise u formatu:
-- --       < dno, ... , vrh >
-- -- (vrh i dno su elementi steka)
-- -- Za prazan stek:  </>

-- instance (Show a) => Show (Stek a) where
--     show Empty = "</>"
--     show a = "<" ++ show' a ++">"
--         where show' Empty = ""
--               show' (Top a Empty) = (show a)
--               show' (Top a s) = (show a)++ ", " ++ show' s

-- -- Instancirati Functor nad `Stek a`
-- instance Functor Stek where
--     fmap f Empty = Empty
--     fmap f (Top a s) = (Top (f a) (fmap f s))