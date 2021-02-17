module Main where

import Lib
import System.Environment  --ovde je funkcija getArgs vraca argumente komandne linije
                           --  getArgs :: IO [String]
                           -- imamo i necistu funkciju readFile
                           --  readFile :: FilePath -> IO String     (FilePath je alias za String)

--print x dodje kao   putStrLn . show x
--ovako mozemo npr napisati program koji ispisuje argumente komandne linije
main :: IO ()
main = do 
    args <- getArgs
    let fileName = head args
    putStrLn $ "Attempting to read file: " ++ fileName
    fileContents <- readFile fileName
    putStrLn fileContents
