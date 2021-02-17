module Main where

--pravimo program koji iz nekog teksta izvlaci najfrekventnije reci

import Lib
import System.Environment
import qualified Data.Char as Char
import qualified Data.List as List
import qualified Data.Tuple as Tuple

--hocemo da koristimo hash mapu za optimizaciju naseg prvog primera. Ovaj paket nije po defaultu
--dostupan vec mora u package.yaml falu da se doda dependancy:    unordered-containters
import qualified Data.HashMap.Strict as HashMap

--NOTE: ako zelimo da ovo pokrenemo sa stack run, argument komandne linije navodimo sa --:
--    stack run -- 5  npr, ako nema  --, 5 ce se tretirati kao arg komandne linije za stack, a ne za nas main program
-- takodje, posto nam se test.txt nalazi u app folderu, a stack run se pokrece iz korenog iz 01_word-count direktorijuma
-- pisemo   cat app/test.txt | stack run --5

main :: IO ()
main = do
    (arg:_) <- getArgs   --odmah dekonstruisemo listu argumenata jer nam treba samo 1 arg
    --mozemo npr funkciju read koristiti za parsiranje Stringa arg u Int
    let n = read arg :: Int    --NOTE: ovde za read moramo proslediti hint kompajleru da bi znao u koji tip prevodimo

    --parsiramo stdin
    --getContents funkcija ce nam odjednom u stringu vratiti sve sa standardnog ulaza
    --NOTE: ova funkcija se cundno ponasa u ghci, ali kad se kompajlira program, radi normalno
    text <- getContents

    --obrada ispis rezultata
    putStrLn $ process text n



--primetimo da je nasa process funkcija skroz cista, nema nikakve IO monade
--onog trenutka kada to ubacimo, morali bismo da povratnu vrednost umotamo u monadu (?)
--dobra praksa je da odvojimo neciste od cistih delova programa

--imamo ugradjenu funkciju words, koja nas string gde su sve reci, razdvaja po belinama u niz reci
--ako koristimo samo words, imacemo tacke i zareze na kraju reci pa je ptorebno nekako da ih ignorisemo
--takodje hocmeo da npr sva slova postanu mala da nebi AAA i aaa tretirao kao razlicite reci

--funckija group uzastopna pojavljivanja nekog elementa liste grupise u zasebnu listu, ali npr
--za [1,1,2,3,4,1,4] vratio bi [[1,1],[2],[3],[4],[1],[4]] pa da nebi imali odvojene slucajeve, stortiramo prvo nasu lsitu reci
--sada pd te liste pravimo parove oblika (rec, broj_pojavljivanja). Sortiranje parova je po dafaultu po prvom
--elementu, a mi zelimo sortiranje po drugom. Prva opcija je da pri mapiranju stavimo da je length prvi clan para
--a drugi je da korisitmo funkciju swap iz Data.Tuple, ona samo okrece torku
--sortiranje je po dafaultu u rastucem poretku, a nama treba opadajuce. Tu mozemo samo na kraju uraditi reverse
--ili u startu sortirati opadajuce pomocu nekih ugradjenih funkcija, umesto sort... mozemo sortBy (flip compare) ...
--na kraju posto nam treba n najfrekventnijih reci, radimo take n, i onda nekako pretvaramo u string, kako nam odgovara

--funkcija lines slicno kao words, razdvaja ne po belinama nego po novim redovima
--funkcija unlines radi obrnuto od lines, sve spoji u jednu
process :: String -> Int -> String
process text n = 
    let ws = words
            $ map Char.toLower
            $ filter (\c -> Char.isLetter c || Char.isSpace c )
            $ text
        word_occs = map (\g -> (head g, length g)) $ List.group $ List.sort ws
        sorted = List.sortBy (flip compare) $ map Tuple.swap word_occs
    in unlines $ map show $ take n $ sorted
        
--mozemo optimizovati process funkciju koriscenjem hash mape. U nju cemo ubacivati pojavljivanja reci
--umesto da sortiramo u prebrojavanju reci
--za HAshMap imamo metode fromList [(k, v)] -> HahMap k v   (naravno mora k da bude u Eq zbog poredjenja)
-- fromListWith dobija i funkciju koja opisuje kako ce se dve iste vrdnosti kljuca spojiti u jednu vrednost
process' :: String -> Int -> String
process' text n = 
    let ws = words
            $ map Char.toLower
            $ map (\c -> if Char.isLetter c then c else ' ')     --jos jedan nacin za ovo filtriranje
            $ text
        word_occs = HashMap.toList $ HashMap.fromListWith (+) [(2, 1) | w <- ws]
        sorted = List.sortBy (flip compare) $ map Tuple.swap word_occs
    in unlines $ map show $ take n $ sorted