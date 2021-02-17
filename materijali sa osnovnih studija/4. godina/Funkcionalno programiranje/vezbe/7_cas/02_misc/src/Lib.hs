module Lib where

someFunc :: IO ()
someFunc = putStrLn "someFunc"

--u ovom primeru malo istrazujemo haskell
--npr hocemo da implementiramo neke funkcije za rad sa polinomima (gde polinom predstavljamo kao listu 
--koeficijenata, npr head liste je najmanji stepen)
--hocemo npr operacije +,-,*,^. Primetimo da klasa Num ima sve te operacije, pa mozemo isntancirati ovu klasu
--za lsitu [a] (pod pretpostavkom da tip a vec mora biti Num (nebitno je da li je ceo broj, float itd))
instance Num a => Num [a] where
    (x:xs) + (y:ys) = (x + y) : (xs + ys)
    xs + [] = xs
    [] + ys = ys

    (x:xs) * (y:ys) = (x*y) :  [x]*ys + xs*(y:ys)
    _ * _ = []

    --da bi bilo Num mora implementirati i ove funkcije ispod, abs=undefined jer nas mrzi
    abs = undefined
    signum = map signum
    fromInteger n = [fromInteger n]
    negate = map (\x -> -x)


--pretpostavimo da hocemo da filtriramo ascii art iz nekog ceta, pri cemu imamo vec dostupne funkcije
--isBraille i isEmoji itd. Umesto da radimo if isBraile || isEMoji ..., mozemo i ovako nesto
--pricao je nesto za Monoide, nisam bas ispratio, ovaj primer je mogao i jednostavnije, samo je hteo da pokaze novo
isForbidden :: Char -> Bool
isForbidden c = getAny $ foldMap (Any .) predicates
    where predicates = [isBraille, isEmoji ...]