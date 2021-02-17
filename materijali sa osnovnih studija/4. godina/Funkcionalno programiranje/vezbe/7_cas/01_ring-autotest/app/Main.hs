module Main where

--hocemo da napravimo neki script koji ce za nas da izvuce sve test funkcije i da ih automatski pokrene
--fajlove u kojima se nalaze testovi cemo prosledjivati kao argumente komandne linije

import System.Environment
import Data.List
import System.Process   --odavde je funkcija system

--ne zaboravi da dodas QuickCheck i process u package.yaml

main :: IO ()
main = do
    args <- getArgs
    --hocemo na neki nacin da obradimo svaki fajl koji se prosledi kao arg komandne linije. Prvi nacin koji
    --nam pada na pamet je nekako pomocu map funkcije, ali posto ce nam operacije verovatno biti
    --neciste, sa IO, mozemo da koristimo mapM  (vidi :doc mapM), tj posto nam ne treba nikakva povratna
    --vrednost koristicemo mapM_
    mapM_ process args
    --alternativno u Control.Monad imamo funkciju forM, koja radi isto ovo, samo su argumenti obrnuti,
    --to je mozda malo citljivije u programerskom smislu:
    --  forM args process   ,ovo dodje kao neki for each

process :: String -> IO ()
process file = do
    contents <- readFile file
    let tests = getTests contents
    if null tests then putStrLn $ file ++ ": nothing to test"
                  else executeTests file tests

--primetimo da je ova funkcija cista, u njoj nemamo IO
--mi ovde treba na neki nacin da parsiramo haskel kod, pa je najbolje da koristimo ugradjene funkcije koje mogu
--da prepoznaju haskell lekseme, kao sto je funkcija lex :: ReadS String, ona ce razdvojiti prosledjen string (u nasem slucaju liniju koda)
--na haskell lekseme. Npr:   lex "foo :: Int -> Int"    vraca   [("foo", " :: Int -> Int")]
--sve nase test funkcije pocinju sa prop_, mozemo to proveravati sa isPrefixOf funkcijom iz Data.List
--psoto npr u fajlu mozemo imati prvo potpis funkc pa onda implementaciju, tj mogu da se pojave dve iste lekseme u listi
--treba izbaciti duplikate, to radi nub funkcija ,npr nub [1,2,3,3,3,4]   vrati   [1,2,3,4]
getTests :: String -> [String]
getTests contents = nub
                  $ filter( "prop_" `isPrefixOf`)    --infiksno pozivamo funkciju, moramo da korisitmo ``
                  $ map (fst . head. lex)      --(\line -> fst $ head $ lex line)
                  $ lines contents


--funkcija writeFile :: FilePath -> String -> IO ()     u fajl na putanji FilePath upisuje sadrzaj iz String
--concatMap je kao flatten u nekim drugim jezicima. On uradi sito sto i map, i onda rezultujucu listu spoji u jednu listu
--system funkcija radi sistemske pozive, i vraca IO ExitCode,a ne samo IO (), poa da nebi prepravljali
--mozemo samo da dodamo da se na kraju vrati prazan IO sa return ()
executeTests :: String -> [String] -> IO ()
--pokazao je i neke boje za tekst u ghci, da nam ispis nasih funkciija bude drugom bojom, ali to nam ne treba, ima na github kodu
--poakzao je i jos alternativne komande koje bismo morali da pisemo ako ne zelimo stack ghci nego obican ghci
executeTests file tests = do
    writeFile "script" $ unlines $ concatMap (makeTest file) tests
    system $ "stack ghci ring-autotest:ring-autotest-test < script"
    return ()

makeTest :: String -> String -> [String]
makeTest file test = ["putStr \"" ++ file ++ ":" ++ test ++ "\\t\"", "quickCheck " ++ test]
--ova funkcija ce nam dati nesto ovako:
--  putStr "file:test"\t"
--  quickCheck test
--konkretno npr:
--  test/Spec.hs:prop_toList_fromList
--  OK, passed 100 tests

