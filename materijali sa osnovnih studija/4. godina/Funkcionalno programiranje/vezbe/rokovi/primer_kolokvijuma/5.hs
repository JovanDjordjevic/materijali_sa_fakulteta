firstLessThan :: Int -> [Int] -> Maybe Int
firstLessThan num lst = if (length processedList) == 0 then Nothing
                        else Just (snd $ head processedList)
                        where processedList = filter (\x -> (fst x) < num) (zip lst [0..])