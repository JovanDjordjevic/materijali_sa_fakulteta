--instancirati nasu klasu Takeable za [], Maybe i stablo

data TreeNode a = End
                | Leaf a
                | TreeNode a (TreeNode a) (TreeNode a) deriving (Show, Eq)

class Takeable t where
    takeSome :: Int -> t a -> [a]

instance Takeable [] where
    takeSome amount lst = take amount lst

--nedovojno informacija u zadatku da bih tacno znao kako ovo treba da se ponasa
instance Takeable Maybe where
    --takeSome amount Nothing = [Nothing]       --ovo ne radi
    takeSome amount (Just a) = replicate amount a
    
toList :: TreeNode a -> [a]
toList End = []
toList (Leaf a) = [a]
toList (TreeNode a left right) = (toList left) ++ [a] ++ (toList right)

instance Takeable TreeNode where
    takeSome amount tree = take amount $ toList tree