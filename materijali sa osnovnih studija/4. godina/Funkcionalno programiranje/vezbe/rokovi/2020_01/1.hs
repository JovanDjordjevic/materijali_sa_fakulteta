module Main where

--NOTE: kad se radi sa getContents, kraj ulaza naznacimo sa Ctrl+D

-- Zadatak 1:
-- Napisati program koji sa standardnog ulaza čita tekst pesme
-- i ispisuje tu pesmu centriranu - poravnatu po sredini u odnosu
-- na najduži stih.
--
-- Na primer, za ulaz:
--
-- As the sun breaks, above the ground,
-- An old man stands on the hill,
-- As the ground warms, to the first rays of light
-- A birdsong shatters the still.
-- His eyes are ablaze,
-- See the madman in his gaze.
--
-- Treba ispisati:
--
--       As the sun breaks above the ground,
--         An old man stands on the hill.
-- As the ground warms to the first rays of light,
--         A birdsong shatters the still.
--              His eyes are ablaze,
--           See the madman in his gaze.
--

main :: IO ()
main = do
    content <- getContents
    let verses = lines content
    let maxLength = foldl (\acc x -> if (length x)>acc then (length x) else acc) 0 verses
    let result = processVerses verses maxLength
    putStr result

processVerses :: [String] -> Int -> String
processVerses verses maxLength = unlines 
                               $ map (\v -> (blanks maxLength v) ++ v ++ (blanks maxLength v)) verses
                        where blanks maxLength v = replicate ((maxLength - (length v)) `div` 2) ' '
