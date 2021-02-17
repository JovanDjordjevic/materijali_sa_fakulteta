data Greska a = Error String
              | Value a
              deriving Show

instance Functor Greska where
    fmap f (Error s) = Error s 
    fmap f (Value a) = Value (f a)
              