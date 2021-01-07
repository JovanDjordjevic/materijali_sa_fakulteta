getmax :: [Float] -> Float
getmax [] = 0.0
getmax lst
    | xs == [] = x
    | x > getmax xs = x
    | otherwise = getmax xs
    where xs = tail lst
          x = head lst

getmin :: Ord a=> [a] -> a
getmin lst
    | tail lst == [] = head lst
    | head lst < getmin (tail lst) = head lst
    | otherwise = getmin (tail lst)

normalize :: [Float] -> Float -> Float -> [Float]
normalize [] _ _ = []
normalize lst newMin newMax = map (\t -> ((t-oldMin)*(newMax-newMin)/(oldMax-oldMin) + newMin)) lst
    where oldMin = getmin lst
          oldMax = getmax lst