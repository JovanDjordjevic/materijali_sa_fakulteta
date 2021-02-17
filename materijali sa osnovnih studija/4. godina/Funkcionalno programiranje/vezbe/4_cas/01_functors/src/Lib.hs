module Lib where

import Prelude hiding (Maybe, Nothing, Just, Either, Left, Right) 
--Prelude je kao neka bazna biblioteka gde imamo sve funkcije i tipove koje smo videli na PP
--hiding ce da ignorise ono sto navedemo, hocemo da sami to implementiramo

--import qualified koristimo ako biblioteci hocemo da damo neki kraci alias npr
import qualified Data.Char as Ch

someFunc :: IO ()
someFunc = putStrLn "someFunc"

-- ako ukucamo u ghci  :i Functor, videcemo nesto ovako:
-- class Functor (f :: * -> *) where ...
-- :: je zapravo kao neki hint kompajleru kako da tretira odredjene tipove
-- * je kind (vrstu) svih nularnih konstruktora (onih koji nemaju nijedan parametar)
-- npr f :: Int je const funkcija koja nema parametar, nego samo Int povratnu vrednost 
-- * -> * znaci da f prima 1 argument,  *->*->* je 2 argumenta itd
--dakle (f :: * -> *) znacio da se f konsturise sa jednim tipskim parametrom  (? nisam bas skapirao sve)

--posto smo uradili hiding Maybe..., nas tip mozemo da nazovemo bas tako
data Maybe a = Nothing
             | Just a
             deriving Show

--za isntanciranje funktora ovde nije (MyMaybe a) zatos to funktor zahteva da jedan tipski
--argument ostane slobodan
instance Functor Maybe where
    fmap f Nothing = Nothing
    fmap f (Just x) = Just (f x)

-- ako ukucamo u ghci  :i Functor, videcemo nesto ovako:  (<$) :: a -> f b -> f a
-- <$ je infiksni operator koji menja vrednost unutar konteksta ali menja kontest (?)
--ubacice a u funktor f (?)
--primer:   3 <$ (Just "b")   vratice   Just 3
--primer:   3 <$ Nothing   vratice   Nothing

--da bi nas tip bio u klasi Functor, dovoljno je da implementira fmap, ne mora da implementira <$
--dakle za nas tip MyJust, dobili bismo ovaj operator gotov jer smo implementirali fmap
--primer:   3 <$ (MyJust "c")   vratice   MyJust 3
--prakticno <$ je kao fmap koji prima argument koji ignorise i umesto njega samo upise vrednost:
--potpis bi joj bio ovako nesto:    f vrednost funktor = fmap (\_ -> vrednost) funktor

-- <$ se zove tako zato sto imamo i <$> sinonim za fmap (taj simbol mozemo da koristimo za infiksno pisanje fmap)
--npr:  (+1) <$> [1,2,3]   je isto sto i     fmap (+1) [1,2,3]

stringToUpper :: String -> String
stringToUpper s = fmap Ch.toUpper s

stringToLower :: String -> String
stringToLower s = fmap Ch.toLower s

makeBold :: String -> String
makeBold s = "<b>" ++ s ++ "</b>"

currentUserName :: Maybe String
currentName = Just "MyName"

formattedUserName :: Maybe String -> Maybe String
formattedUserName username = fmap makeBold $ fmap stringToUpper username
--moglo je i kompozicijom
formattedUserName' :: Maybe String -> Maybe String
formattedUserName' username = (fmap makeBold) . (fmap stringToUpper) username


data Either a b = Left a
                | Right b
                deriving (Show, Eq)

type StrErr a = Either String a

--isntanciranje funktora za Either mora (Either a), a ne samo Either, jer jedan mora da bude slobodan (?)
instance Functor (Either a) where
    fmap f (Left x) = Left x
    fmap f (Right x) = Right (f x)

--ako uradimo :i Functor u ghci videcemo izmedju ostalog da ((->) r) isntancira funktor. Kao sto mozemo napisati 
-- 3 + 4 kao (+) 3 4 tako mozemo napisati: (->) a b umesto a -> b. Strelica je zapravo funkcija koja jekosnturktor funkcije sa
--jednim argumentom, a ((->) r) je parcijalno primenjena funkcija ->
instance Functor ((->) r) where
    fmap f g = (\x -> f (g x))  -- u prevodu ovo je kompozicija funkcija f i g. Mozemo pisati   fmap f g = (.)

--kompoziciju funkcija mozemo posmatrati kao funktor. U rpevodu, ako imamo npr 
--kompoziciju funkcija: let f = (+1).(*3)  i onda uradimo   fmap (*2) f, dobili smo (*2).(+1).(*3)

--ZAsto smo pricali sve ovo? Ideja je da mi uzmemo neku funkciju, npr (+1) i da pomocu fmap uradimo
-- 'lifting' te funkcije, tj da mi sada to (+1) ne mozemo samo da primenjujemo na brojeve, vec na bilo koji funktor 
--koji u sebi sadrzi vrednost na koju (+1) moze da se primeni, pri cemu se kontekst odrzava
--Npr: funkcija replicate (primer replicate 2 "c" vraca "cc"):
--fmap (replicate 3) (Just 1)  vraca  Just [1,1,1]       ovde je kontekst bio Maybe, i on je odrzan
--fmap (replicate 3) [1,2]    vraca  [[1,1,1], [2,2,2]]  ovde je kontekst bio lista i on je odrzan
--fmap (replicate 3) (Left 1) vraca Left 1   ovde je kontekst bio Either, a u Either se radi nesto samo sa desnim vrednostima, pa ovde nije uradjeno nista
--fmap (replicate 3) (Right 3) vraca Right [3,3,3]  ovde je bila desna vrednost Either, pa je parcijalana funkcija replicate 3 primenjena


--svaki funktor mora da prati nekakva dva zakona:
-- 1)   fmap id = id
-- 2)   fmap (f.g) = (fmap f) . (fmap g)