sameChars :: String -> Bool
sameChars s = any (\e -> if (fst e)==(snd e) then True else False) $ zip s (tail s)