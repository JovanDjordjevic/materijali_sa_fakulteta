type Tacka = (Float, Float)

tacka :: Float->Float->Tacka
tacka x y = (x,y)

o :: Tacka
o = tacka 0.0 0.0

type Putanja = [Tacka]

putanja :: [Tacka] -> Putanja
putanja lst = lst 

duzinaPutanje :: Putanja -> Int
duzinaPutanje p = length p 

transliraj :: Tacka->Float->Float->Tacka
transliraj t xt yt = (fst t + xt, snd t + yt)

rastojanje :: Tacka->Tacka->Float
rastojanje (x1,y1) (x2,y2) = sqrt $ (x1-x2)^2 + (y1-y2)^2

uKrugu :: Float->[Tacka]->[Tacka]
uKrugu r lst = [t | t<- lst, rastojanje o t < r]

translirajPutanju :: Putanja->Float->Float->Putanja
translirajPutanju p x y = map (\t -> transliraj t x y) p

nadovezi :: Tacka->Putanja->Putanja
nadovezi t putanja = reverse $ t : (reverse putanja) 

spojiPutanje :: Putanja->Putanja->Putanja
spojiPutanje p1 p2 = p1 ++ p2 

centroid :: [Tacka]->Tacka
centroid ts = tacka prosekX prosekY
    where prosekX = prosek $ map fst ts
          prosekY = prosek $ map snd ts
          prosek lst = (sum lst) / (fromIntegral $ length lst)

kvadrantTacke :: Tacka->Int
kvadrantTacke (x,y)
    | x > 0 && y > 0 = 1
    | x < 0 && y > 0 = 2
    | x < 0 && y < 0 = 3
    | x > 0 && y < 0 = 4
    | otherwise = 0

kvadrantPutanje :: Putanja->Int
kvadrantPutanje lst = if istiKvadranti then head kvadranti else 0
    where kvadranti = map kvadrantTacke lst 
          istiKvadranti = all (== head kvadranti) (tail kvadranti)

tackeUKvadrantu :: Int->[Tacka]->[Tacka]
tackeUKvadrantu k lst = filter (\t -> (kvadrantTacke t) == k) lst

tackeVanKvadranta :: Int->[Tacka]->[Tacka]
tackeVanKvadranta k lst = filter (\t -> (kvadrantTacke t) /= k) lst

maksimumi :: [Tacka] -> (Float, Float)
maksimumi lst = (maksimum $ map fst lst , maksimum $ map snd lst)
    --where maksimum lst = foldl (\acc x -> if acc > x then acc else x) (head lst) (tail lst)
    where maksimum lst = foldl1 max lst



 :: Int->[a]->[a]
izbaci k lst
        | k<0 = lst
        | k>=length lst = lst
        | otherwise [ (lst !! i) | i<-[0,(length lst)-1],i /=k]