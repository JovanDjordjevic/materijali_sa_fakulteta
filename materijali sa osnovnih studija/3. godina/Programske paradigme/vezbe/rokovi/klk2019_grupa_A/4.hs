import Data.List as List

best :: [([Char], [Int])] -> [[Char]]
best [] = []
best lst = map (\p -> fst p) $ filter (\t -> (ima (snd t)) >= 2 ) lst
 
ima :: [Int] -> Int
ima [] = 0
ima lst 
    | head lst > 1 = 1 + ima (tail lst)
    | otherwise = ima (tail lst)

{- ne znam kako da uradim sortiranje -}
order :: [([Char],[Int])] -> [(Int, [Char], Int)]
order lst = map(\t -> (0,fst t, ima (snd t))) lst

{-let ucenici = [ ("Ana",[4,3,1,5]), ("Anja", [2,3,4]), ("Iva", [2,1,1,5]) ] -}