import Lib

import Test.QuickCheck

main :: IO ()
main = putStrLn "Test suite not yet implemented"

--testovi su funkcije oblika a->Bool
--neka kao konvencija u QuickCheck biblioteci je da imena funkcija testova pocinju sa prop_
--ovaj test proverava da li je uneta lista ista kao i kad se nad njom pozove toList fromList
--mozemo ispod i eksplicitno navesti kog tipa je nasa promenljiva lst
prop_conversions lst = 
    lst == (toList $ fromList lst)
    where types = (lst :: [Int])
--iz interpretera mozemo da testiramo ovo, tako sto pozovemo funckiju quickCheck kojoj kao argument
--prosledimo nasu ovu prop_ funkciju, npr:  quickCheck prop_conversions
--quickCheck ce automatski generisati ulaze za ovaj test i ispisace ako je neki test pao
--npr ovaj prvi test je pao za ulaz [0], pa to menjamo u Lib

--testiramo npr focusPrevious i focusNext
prop_fp_fn lst = 
    lst == (toList $ focusNext $ focusPrev $ fromList lst)
    where types = (lst :: [Int])

--ako zelimo da se generise neki odredjen broj testova, npr 10000 koristimo funkciju withMaxSuccess
--npr:
--  quickCheck $ withMaxSuccess 1000 prop_conversions

prop_fn_fp lst = 
    lst == (toList $ focusPrev $ focusNext $ fromList lst)
    where types = (lst :: [Int])