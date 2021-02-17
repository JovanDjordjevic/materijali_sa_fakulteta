module Zad2 where

--NOTE: imam ovde u ispisu jedan pogresan razmak

-- Zadatak 2:
-- Definisati tip podataka `TreeNode a` koji predstavlja cvor jednog binarnog
-- stabla. Svaki cvor ima ili levog i desnog sina, ili moze imati specijalnu
-- oznaku `End` koja se koristi da oznaci prazan cvor.
--

data TreeNode a = End
                | Leaf a
                | NodeValue a (TreeNode a) (TreeNode a)

-- Instancirati Show nad definisanim tipom prateci in-order obilazak stabla.
--
--          7
--        /   \
--       3     9
--        \   / \
--         4 8  10
--
-- rezultat: [3 4 7 8 9 10]

-- NodeValue 7 (NodeValue 3 (End) (Leaf 4)) (NodeValue 9 (Leaf 8) (Leaf 10))

instance (Show a) => Show (TreeNode a) where
    show t = "[" ++ (show' t) ++ "]"

show' :: (Show a)=> TreeNode a -> String
show' End = ""
show' (Leaf a) = show a
show' (NodeValue a left right) = (show' left) ++ " " ++ (show a) ++ " " ++ (show' right)