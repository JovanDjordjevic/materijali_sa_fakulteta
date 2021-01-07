type Racun = (String, Int)

sadrzi :: [(String,Int)] -> String -> Bool
sadrzi [] br = False
sadrzi (x:xs) br
    | fst x == br = True
    | otherwise = sadrzi xs br


otvori :: [(String,Int)] -> String -> [(String,Int)]
otvori b br 
   | (sadrzi b br ) == True = b
   | otherwise = (br,0) : b

zatvori :: [(String,Int)] -> String -> [(String,Int)]
zatvori [] br = []
zatvori b br 
    | (fst (head b)) == br = zatvori (tail b) br
    | otherwise = (head b) : zatvori (tail b) br

uplati :: [(String,Int)] -> String -> Int-> [(String,Int)]
uplati [] br iznos = []
uplati b br iznos
    | (fst (head b)) == br = (br, (snd (head b) + iznos)) : uplati (tail b) br iznos
    | otherwise = head b : uplati (tail b) br iznos

{-
otvori [("acc-007", 5), ("acc-005", 6)] "acc-003"
zatvori [("acc-007", 5), ("acc-005", 6)] "acc-007"
uplati [("acc-007", 5), ("acc-005", 6)] "acc-007" 5
-}