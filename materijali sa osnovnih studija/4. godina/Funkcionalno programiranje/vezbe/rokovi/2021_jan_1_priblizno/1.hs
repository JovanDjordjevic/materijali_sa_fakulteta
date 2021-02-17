--imena fajlova se daju kao argumenti komandne linije i ucitava se rec sa stdin
--prebrojati pojavljivanje reci u fajlovima

import System.Environment
import qualified Data.Char as Ch

--OVO U KOMENTARU RADI ZA 1 FAJL, OVO ISPOD MI NE RADI
-- main :: IO()
-- main = do
--     (x:_) <- getArgs
--     fileWords <- readFile x
--     putStrLn $ show $ foldl (\acc s -> if s=="main" then acc + 1 else acc ) 0 $ words $ map Ch.toLower $ filter (\c -> if Ch.isSpace c then True else if Ch.isAlphaNum c then True else False) fileWords

main :: IO()
main = do
    files <- getArgs
    wordToFind <- getContents
    --let occurences = findOccurences wordToFind files
    let fileContents = [ s | f<-files, s<- readFile f ]
    putStrLn $ show fileContents
    putStrLn $ show wordToFind

-- findOccurences :: String -> [String] -> Int
-- findOccurences wordToFind files = sum $ map (\f -> processOneFile wordToFind f) files

-- processOneFile :: String -> String -> Int
-- processOneFile wordToFind file = do
--                                 fileWords <- readFile file
--                                 --let splitWords = 
--                                 foldl (\acc s -> if s==wordToFind then acc + 1 else acc ) 0 $ words $ map Ch.toLower $ filter (\c -> if Ch.isSpace c then True else if Ch.isAlphaNum c then True else False) fileWords

