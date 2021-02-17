import Data.Char   --za primere sa niskama

--primer funkcije za sumrianje niza
mySum :: Num a => [a] -> a
mySum [] = 0
mySum (x:xs) = x + (mySum xs)

--priemr repno rekurzivne funckije za sumiranje niza
mySum' :: Num a => [a] -> a
mySum' xs = mySumHelper 0 xs
    where mySumHelper acc values = case values of
                                        [] -> acc
                                        (x:xs) -> mySumHelper (acc + x) xs

--priemr funkcije za filtriranje, prvi arg je funkcija koja vraca bool vrednost da li tekuci
--element treba da se zadriz u listi. Funlcije ovog tipa (koje uzmu 1 arg i vrate bool) se
--generalno zovu prediakti
myFilter :: (a -> Bool) -> [a] -> [a]
myFilter _ [] = []
myFilter p (x:xs) = 
    let filteredTail = myFilter p xs
    in if p x then x : filteredTail else filteredTail

--myFilter sa repnom rekurzijom
--NOTE: primetimo da ako izvrsimo ovu funkciju, ona ce filtrirati lepo ali ce vratiti listu u obrnutom
--redosledu, zbog x:acc. Resenje za ovo (ako zelimo) je da u startu obrnemo pocetnu listu, tj da u liniji
--28 stavimo myFilterHelper [] (reverse xs)
myFilter' :: (a -> Bool) -> [a] -> [a]
myFilter' _ [] = []
myFilter' p xs = myFilterHelper [] xs
    where myFilterHelper acc values = case values of
                                        [] -> acc
                                        (x:xs) -> myFilterHelper (if p x then x:acc else acc) xs

--mySum pomocu foldl
mySum'' xs = foldl (\acc x -> acc + x) 0 xs
--mozemo malo da skratimo zapis (izbrisemo xs jer se nalazi na kraju)
--  mySum'' = foldl (\acc x -> acc + x) 0 
--mozemo jos da skratimo
--  mySum'' = foldl (+) 0

--myFilter pomocu foldl, (reverse da bi se ocuvao redosled)
myFilter'' :: (a -> Bool) -> [a] -> [a]
myFilter'' p xs = foldl (\acc x -> if p x then x:acc else acc) [] (reverse xs)
--moglo je i sa foldr, pa onda nemamo reverse (ali moramo i da obrnemo argumente)
--  myFilter'' p xs = foldr (\x acc -> if p x then x:acc then acc) [] xs

--nadovezivanje lsite sa fold (ideja je da redom na desnu listu (ona je acc) ubacjemo elemente leve lsit)
myConcat :: [a] -> [a] -> [a]
myConcat ls rs = foldr (\x acc -> x:acc) rs ls
--  (\x acc -> x:acc)   je skraceno samo (:)

----------------------------------------------------------------------------------------
--primer sa niskama:
----------------------------------------------------------------------------------------

--hocemo da izvucemo prvu rec iz recenice. U haskelu je String alias za [Char], i sve operacije koje rade
--nad listama, rade i za Stringove. takeWhile uzima elemnte liste sve dok je prosledjeni predikat tacan
--isSpace je iz Data.Char. Posto uzimamo slova sve dok nisu beline, moramo da radimo kompoziciju sa not
--to se radi sa . :     not . isSpace. Zeleli bismo da uklonimo sve beline sa pocetka reci ako ih ima, tako da
--za to mozemod a koristimo dropWhile
takeWord :: String -> String
takeWord sentence = takeWhile (not . isSpace) (dropWhile isSpace sentence)

----------------------------------------------------------------------------------------

--hocemo da filtriramo po indeksu iz neke kolekcije, tj da vratimo elemente po indeksu
--koje zadovoljavaju neki predikat p. Ako zipujemo listu brojeva sa kolekcijom, u sustini
--dobijamo listu parova (indeks, element). 
filterByIndex p xs = 
    let withIndices xs = zip [1..] xs
        indexed = withIndices xs
        pairpred = p . fst
    in map snd $ filter pairpred indexed

