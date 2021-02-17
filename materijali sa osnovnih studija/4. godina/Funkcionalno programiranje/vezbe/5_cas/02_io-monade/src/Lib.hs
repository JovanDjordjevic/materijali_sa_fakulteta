module Lib where

--kad procitas Lib.hs, otvori Main.hs, tu ima primer 

--haskel je cist funkcionalni jezik, i zbog toga ne mozemo da imamo funkcije koje nemaju povratnu vrednost
--kao sto je npr getLine, haskel to resava tako sto nam daje "kutiju" u koju ce taj string sto vrati getLine da se upise
--poledajmo potpis main funkcije, main :: IO () ,primetimo da moramo da stavimo zagrade kada nema povratnu vrednost
--tj kada u IO kutiji ne treba da se nalazi nista

--poglejajmo tipove nekih "necistih" funkcija:   
--getLine :: IO String,    puStr :: String -> IO (),    putStrLn :: String ->IO ()

-- ako bismo hteli da nanizemo pozive tri putStrLn funckije, nebi smo mogli da radimo to ovako:
-- putStrLn "a" >>= putStrLn "b" >>= putStrLn "c" zato sto bind pokusava da izracuna vrednost sa leve strane
-- i onda to da primeni na desnu, a iz potpisa putStrLn se vidi da on nema povratnu vrednost
-- ovo bismo npr mogli:   getLine >>= putStrLn   ,zato sto getLine ne vraca prazan IO

--zbog ovih stituacija imamo >>, jer njemu ne treba izracuanta vrednost sa leve stranne
-- putStrLn "a" >> putStrLn "b" >> putStrLn "c"   je okej

--mana  >> je sto cim ga iskoristimo, gubimo informaciju o svemus to je bilo sa leve strane, dakle nebi
--nebi mogli da cas imamo a cas nemamo povratnu vrednost
--za ovo mozemo u main funkiji da koristimo 'do' notaciju ('do' ne radi samo za IO vec moze za bilo koju monadu)
main' :: IO ()
main' = do 
    line <- getLine   --ova linija kaze, sta god je vrednost ove monade desno, izvuci je i imenuje je kao line
                      -- i onda u pozivima ispod mozes da je koristis
    putStrLn line
    putStrLn line
    putStrLn line

--mozemo 'do' koristiti slicno kao naredbe u drugim jezicima. Moze se pisati i ovako:
--  main = do { ... ; ... ; ... ; ... }    

foo :: Maybe String
foo = do
    x <- Just 3
    y <- Just "!"
    Just (show x ++ y) --ovu poslednju liniju mozemo na neki nacin gledati kao povratnu vrednost funkcije foo
    --umesto Just (show x ++ y) ovde je moglo da stoji 
    --  return $ show x ++ y, jer return bacuje u kontekst, a ovde je kontekst ocigledno Maybe (?)

--npr hocemo da implementiramo input funkciju kao u pajtonu
--ispisemo poruku, ignorisemo povratnu vrednost od putStrLn jer je i nema, i onda uzimamo liniju sa getLine
input :: String -> IO String
input message = putStrLn message >> getLine

main'' = do
    x <- input "unesi nesto"
    y <- input "uensi nesto drugo"
    putStrLn "nesto"

