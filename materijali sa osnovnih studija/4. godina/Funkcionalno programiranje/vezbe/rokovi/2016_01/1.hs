isSorted :: (Ord a) => [a] -> Bool
isSorted [] = True
isSorted [x] = True
isSorted lst = 
             if all (\e -> if e == (head lst) then True else False) (tail lst) then True
             else if all (\e -> if (fst e) <= (snd e) then True else False) (zip lst (tail lst)) then True
             else if all (\e -> if (fst e) >= (snd e) then True else False) (zip lst (tail lst)) then True
             else False 