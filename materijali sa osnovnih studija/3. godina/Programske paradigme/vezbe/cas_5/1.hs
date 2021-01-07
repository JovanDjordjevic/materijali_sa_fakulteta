--komentar
{-
gwgaeg
egsgcn
-}

parni n = parni' n 1
    where parni' n i
            | i == n = [i*2]
            |otherwise = [i*2] ++ parni' n (i+1)
