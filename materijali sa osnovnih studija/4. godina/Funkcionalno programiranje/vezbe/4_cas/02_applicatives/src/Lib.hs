module Lib where

someFunc :: IO ()
someFunc = putStrLn "someFunc"

--da bi nesto bilo Applicative, ono mora biti Functor. U haskelu izmedju nekih tipova psotoji hijerarhija
--da bi nesto instanciralo Applicative, ono mora da implementira funkciju pure i pored nje
--jendu od:  <*>   ili liftA2     ,vidi potpise u ghci sa :i Applicative

-- :t pure    ispisuje    pure :: Applicative f => a -> f a

--Applicative mozemo posmatrati kao kutiju, slicno kao funktor. Prosledimo vrednost i vrati nam se kutija
--sa tom vrednoscu u sebi. pure zapravo radi "umotavanje" vrednosti u nekakav kontekst

-- :t (<*>)   ispisuje (<*>) :: Applicative f => f (a -> b) -> f a -> f b 
--vidimo da ima slican potpis kao fmap

--primer:    fmap (+1) $ Just 3    vraca   Just 4
--primer:    Just (+1) <*> Just 3  vraca   Just 4
--znaci <*> je slican kao fmap, samo sto on prvo izvuce funkciju iz konteksta i onda da je primeni na neki drugi konteks
--ovaj operator se cesto zove i "apply"

--Functori uzimaju parcijalne funkcije jednog argumenta, dok nam Applicative omogucava da radimo i sa funkcijama vise argumenata (?)
--npr (+) je funkc sa 2 arg:
-- Just (+) <*> Just 3   --ovim smo doblili parcijalnu funkciju koja cuva kontekst (?)
-- Just (+) <*> Just 3 <*> Just 4     ispisuje      Just 7
-- Just (+) <*> Nothing <*> Just 4     ispisuje      Nothing

--mozemo da nanizemo apply operator koliko god puta hocemo, tj koliko god funkcija koju prosledimo ima argumenata
--jedina mana je sto funkciju prvo moramo da umotamo u Functor da bi je primenili (?)

--  fmap (+3) $ Just 3    vraca Just 6
-- Just (+3) <*> Just 3   vraca Just 6   morli smo prvo da kazemod a je kontekst funkcije (+3) Maybe
-- pure (+3) <*> JUst 3   vraca Just 6   pure umotava u kontekst, mogli smo i sa tim

--kako npr instanciramo tip Mayvbe za klasu Applicative:
instance Applicative Maybe where
    pure x = Just x                         --mormao da implementiramo pure
    (<*>) Nothing _ = Nothing               --moramo da implementiramo <*>   (ili umesto nje liftA2)
    (<*>) _ Nothing = Nothing
    (<*>) (Just f) (Just x) = Just (f x)
    --ako je u bilo kom trenutku Nothing, on mora da se propagira do kraja

-- pure f <*>   je ekvivalentno sa     fmap f x

--za liste
instance Applicative [] where
    pure x = [x]
    --u ghci:  [(+1), (+2)] <*> [1,2,3]     vraca     [2,3,4,3,4,5]
    --tj vidimo da se svaka f iz liste funkcija primenila na sve elemente liste, ovo nije bas intutivno kako bismo ocekivali da se ponasa
    (<*>) fs xs = [f x | f <- fs, x <- xs]

    --mozemo npr da napisemo ovako nesto: [(+), (+)] <*> [1,2,3]   tu smo zapravo dobili listu funkcija gde 
    --su obe parcijalno rpimenjene na svaki element liste (?)

--neke funkcije za Applicative se nalaze u modulu Control.Applicative (?)

--liftA2 radi isto sto i fmap samo za funkcije sa 2 argumenta
--      nasLiftA2 f a b = f <$> a <*> b

--sequenceA funkcija iz liste aplikativa izvlaci vrednosti, ubaci u novu lsitu i umota u kontekst:
--  sequenceA [Just 3, Just 4, Just 5]    vraca Just [3,7,4]
--  sequenceA [Just 3, Nothing, Just 5]   vraca Nothing
--  sequenceA [(+3), (+2), (+1)]  3       vraca [6,5,4]
--  sequenceA [[1,2,3], [2,3,4]]          vraca [[1,2],[1,3],[1,4],[2,2],[2,3],[2,4],[3,2],[3,3],[3,4]]
--  sequenceA [[1,2,3], [2,3,4], []]      vraca []

--imamo i "delimicne apply-jove"    <*   i  *>
-- :t (*>)    vrati   Applicative f => f a -> f b -> f b
--npr:  Just 4 <* Just "a"   vrati  Just 4
--npr:  Nothing <* Just "a"  vrati  Nothing
--npr:  Just 4 <* Nothing    vrati  Nothing

--npr:  Just 4 *> Just 5    vrati  Just 5

--ako su i leva i desna vrednost u redu, vrati onu na koju <* ili *> pokazuje   (?)