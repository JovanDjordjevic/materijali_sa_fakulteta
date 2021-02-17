--definisati data za stablo i instancirati show, eq i functor

data TreeNode a = End
                | Leaf a
                | TreeNode a (TreeNode a) (TreeNode a)

instance (Show a) => Show (TreeNode a) where
    show tree = "[" ++ show' tree ++ "]"
        where show' End = ""
              show' (Leaf a) = show a
              show' (TreeNode a left right) = show' left ++ " " ++ show a ++ " " ++ show' right


instance (Eq a) => Eq (TreeNode a) where
    t1 == t2 = (toList t1) == (toList t2)
        where toList :: TreeNode a -> [a]
              toList End = []
              toList (Leaf a) = [a]
              toList (TreeNode a left right) = (toList left) ++ [a] ++ (toList right) 

instance Functor TreeNode where
    fmap f End = End
    fmap f (Leaf a) = Leaf (f a)
    fmap f (TreeNode a left right) = TreeNode (f a) (fmap f left) (fmap f right)

