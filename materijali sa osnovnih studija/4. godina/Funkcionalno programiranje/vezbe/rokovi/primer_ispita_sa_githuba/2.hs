module Main where

--NOTE: u ovom zadatku sam radio prevodjenje, a ne iz interpretera. Da bi se program pokrenuo, moramo imati module Main where...
--umesto onog sto je stajalo (module Zad2 where...) i moramo imati main funkciju

-- Zadatak 2:
--
-- Napisati program koji iz fajla čija je putanja data kao argument 
-- komandne linije, čita brojeve jedan po jedan, svaki u zasebnom redu.
-- Program ispisuje sve brojeve poravnate udesno u odnosu na najduži
-- broj, a zatim podvlaku i sumu svih brojeva
--
-- Na primer, za fajl:
--
-- 1020
-- 10
-- 3
-- 8000
-- 2000
-- 1
--
-- Treba ispisati:
--
--      1020
--        10
--         3
--      8000
--      2000
--         1
--     -----
--     11034

import System.Environment

main :: IO()
--main = putStrLn "beans"
main = do
    (x:_) <- getArgs
    file <- readFile x
    let fileLines = lines file
    let resSum = calculateSum fileLines
    let sumLen = length $ show resSum
    putStr $ numsToString fileLines sumLen
    putStrLn $ replicate sumLen '-'
    putStrLn $ show resSum

calculateSum :: [String] -> Int
calculateSum fileLines = sum $ map (\line -> read line) fileLines

numsToString :: [String] -> Int -> String
numsToString fileLines sumLen = unlines 
                       $ map (\s -> addBlanks s) fileLines 
                       where addBlanks s = (replicate (sumLen - length s) ' ') ++ s
