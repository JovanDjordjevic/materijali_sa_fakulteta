whichSort :: (Ord a) => [a] -> String
whichSort [] = "EQ"
whichSort lst 
            | (head lst) == (head $ reverse lst)  = "EQ"
            | (head lst) > (head $ reverse lst)   = "GT"
            | (head lst) < (head $ reverse lst)   = "LT"
            | otherwise                           = "ne moze da se desi"
