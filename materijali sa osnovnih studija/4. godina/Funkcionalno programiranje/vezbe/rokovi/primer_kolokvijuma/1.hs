countGreater_recursive :: (Ord a)=>[a] -> Int
countGreater_recursive [] = 0
countGreater_recursive (x:xs) = countHelper_recursive x xs
                            where countHelper_recursive _ [] = 0
                                  countHelper_recursive firstElem rest = if (head rest) > firstElem then 1 + countHelper_recursive firstElem (tail rest)
                                                                         else countHelper_recursive firstElem (tail rest)

countGreater_fold :: (Ord a)=>[a] -> Int
countGreater_fold [] = 0
countGreater_fold (x:xs) = foldl (\acc e -> if e>x then acc + 1 else acc) 0 xs

countGreater_none :: (Ord a)=>[a] -> Int
countGreater_none [] = 0
countGreater_none (x:xs) = sum $ map (\e -> if e>x then 1 else 0) xs

prop_comp :: (Ord a)=>[a] -> Bool
prop_comp lst = 
    (countGreater_recursive lst) == (countGreater_fold lst)