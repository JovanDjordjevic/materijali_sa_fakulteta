module Lib where

someFunc :: IO ()
someFunc = putStrLn "someFunc"

--u Control.Applicative, pored Applicative imamo i Alternative klasu. Da bi nesto bilo Alternative
--mora vec biti Applicative i implementirati metode   empty   i    <|>      (npr Maybe tip je Alternative)
-- :t empty    vrati   empty :: Alternative f => f a
--empty radi kao nasuprot pure (?)
-- npr:   pure 4 :: Maybe Int   vraca  Just 4
-- npr:   empty :: Maybe Int    vraca  Nothig

-- :t <|> vraca   <|> :: Alternative f => f a -> f a -> f a    (pprimi dva alternativa i vrati alternativ)
-- npr: Just 4 <|> Just 3                  vraca Just 4
-- npr: Nothing <|> Just 3                 vraca Just 3
-- npr: Nothing <|> Nothing                vraca Nothing
-- npr: Nothing <|> Nothing <|> Just 4     vraca Just 4
-- Dakle, <|> radi sledece: koliko god alternativa mu damo, on vraca prvi koji nije empty

--npr instanciramo sami ALternative za Maybe    (pominjemo sada Alternative jer ce nam biti korisni kasnije)
instance Alternative Maybe where
    empty = Nothing
    
    Nothing <|> r = r
    l       <|> _ = l


makeItalic :: String -> String              --obicne funkcije, znamo da pravimo njihovu kompoziciju
makeItalic s = "<i>" ++ s ++ "</i>"

makeUnderlined :: Maybe String -> Maybe String  --isto
makeUnderlined Nothing = Nothing
makeUnderlined (Just s) = Just ("<u>" ++ s ++ "</u>")

--stavari se komplikuju kada treba da pravimo kompoziciju npr ovakvih funkcija, gde oan primi neki tip a vrati Maybe nesto
--treba nam nacin da se to Maybe propagira dalje
makeBold :: String -> Maybe String      
makeBold s = Just $ "<b>" ++ s ++ "</b>"

stringToUpper :: String -> Maybe String
stringToUpper s = Just $ fmap Data.Char.toUpper s

--npr ako bismo komponovali stringToUpper . makeBold,  rezltat bi bio neki Just(Just "nesto")
--itd ako bismo ih jos nizali bilo bi JUst(JUst(Just....))). Ovo mozda ne zelimo
--zelimo na neki nacin da propagiramo greske koje se dese a da pritom cuvamo kontekst (?)
--za to nam sluze monade

--da bi nesto bilo Monad mora da bude Applicative (a psoto je Applicative i Functor, monada je takodje Functor)
--Monade su dosle iz potrebe da nizemo one funkcije problematicnog tipa, kao iznad. Tu imamo operator
--funckiju (>>=) (zove se i bind operator) koja mora da se implementira da bi se instancirala Monad klasa (imamo i (>>) koja ne mora da se implementira)
-- :t (>>=)   vraca    (>>=) :: m a -> (a -> m b) -> m b  (dakle primi monadu, primi funkciju i vrati monadu)

--imamo jos funkcije return i fail.
-- :t return   vrati   return :: Monad m => a -> m a   (slican potpisima kao pure)
--ao probamonna primeru videcemo da pure i return rade identicnu stvar. Razlog sto postoje kao dve razlitie stvari
--je zbog nekih ranijih verzija haskela gde nije psotojala Applicative klasa u hijerarhiji, bilo je samo  Functor -> Monad

-- sa bind operatorom mozemo da nizemo onakve funkcije

--objasnicemo sve ovo na nekom primeru. Imamo klovna koji seta na zici i drzi onaj veliki stap
--na levi i desni kraj stapa mogu da slete ptice, a klovn moze da se odrzi na zici ako je
--npr razlika broja ptica sa leve i desne strane najvise 3 
type Birds = Int
type Pole = (Birds, Birds) --br ptica sa leve i s adesne strane

landLeft' :: Birds -> Pole -> Pole
landLeft' n (left, right) = (left + n, right)

landRight' :: Birds -> Pole -> Pole
landRight' n (left, right) = (left, right + n)

--da nebi u ghci sve pisali u obrnutom poretku zbog kompozicije, mozemo npr uvesti ovu funkc
x -: f = f x
--npr pozvi u ghci bi bili:   (0,0) -: land Left 3 -: landRight 2 ...

--landLeft koji mozda vrati stap ako klovn nije pao
landLeft :: Birds -> Pole -> Maybe Pole
landLeft n (left, right)
    | abs (left + n - right) < 4 = Just (left + n, right)
    | otherwise                  = Nothing

landRight :: Birds -> Pole -> Maybe Pole
landRight n (left, right)
    | abs (left - (right + n)) < 4 = Just (left, right + n)
    | otherwise                    = Nothing

--kada sada komponujemo ove landLeft i landRight funckije sa bind operatorom  >>= desice 
--se da ce se Nothing propagirati do kraja kako treba


--primer kako bismo npr isntancirali Monad za Maybe
instance Monad Maybe where
    return = Just
    
    Nothing >>= f = Nothing
    Just x >>= f = f x

instance Monad [] where
    return x = [x]
    xs >>= f = concat $ map f xs     --ovu implementaciju smo zakljucli tako sto smo probali u ghci da radimo bind na listi


--Za Monade, kao i za Functore, psotoje nekakvi zakoni (nece nam traziti ovo na vezbama)
-- return x >>= f     ekvivalentno sa    f x
-- m >> return        ekvivalentno sa    m

-- razlika izmedju >> operatora i >>= operatora kad se pokrene :t  je samo u drugom argumentu
--tj >> ne prima funkciju nego vrednost. (? >> radi isto sto i bind samo sto ignorise levu vrednost,
--bind u sustini izracuna levu vrednost i to prosledi desnoj, a >> samo odradi levu, pa odradi desnu ?)

--kako bismo sami implementirali (>>) ?
--ovako:        f x y = x >>= (\_ -> y)