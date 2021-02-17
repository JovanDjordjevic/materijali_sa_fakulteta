module Lib where

someFunc :: IO ()
someFunc = putStrLn "someFunc"

--newType koristimo kada nam treba novi tip koji u konstruktoru prima samo jedan argument
--ako nam treba vise argumenata, moramo da koristimo data. newType je optimizovan i ako mozemo da 
--ga koristimo, treba da ga koristmo

--u data mozemo i da imenujemo argumente, pri cemu ovo regId, name... nisu samo imena ovig argumenata
--vec su ujedno funkcije koje se mogu ponasati kao geteri. Ovi geteri su viljivi na globalnom nivou, tako da
--ne mozemo imati jos jedan tip kojima se ti geteri zovu isto (?)
data Pet = MkPet { regId  :: Int
                 , name   :: String
                 , age    :: Int
                 , height :: Float
                 , weight :: Float
                 } deriving (Show, Eq)

--deriving Eq ce nam dati podrazumevanu implementaciju za poredjenje dve instance (po defaultu je to poredjenje po svakom polju)
--deriving Show ce nam dati neku default implementaciju show metoda koji ce omoguciti da se nasa klasa ispise kao string
--instancu naseg tipa mozemo u interpreteru napraviti na vise nacina:
--  MkPet 1 "ime" 5 100 100
--  MkPet {regId = 1, age = 5, weight =100, height = 100, name = "ime"}      --primetimo da ovde nije bitan redosled polja konstruktora
--  let myPet = MkPet 1 "ime" 5 100 100
--sa let smo "sacuvali ovo u promenljivu", a sada ako zelimo da napravimo novi Pet koji ima ista sva polja
--kao myPet sem npr. name polja, napisali bismo:
--  myPet {name = "drugo_ime"}

data Circle = MkCircle { r :: Float }
data Rectangle = MkRectangle {a :: Float, b :: Float}

--klase u haskelu funkcionisu vise kao interfejsi, oni samo govore koje funkcije neki tip 'a' mora da implementira (?)
--navodimo koje su to funkcije i koji su njihovi potpisi
class Shape a where
    area           :: a -> Float
    circumference  :: a -> Float  

--isntanciramo klasu za nas tip Circle i za Rectangle, moramo imeplementirati funkcije koje smo naveli iznad
instance Shape Circle where
    area            x = (r x) * (r x) * pi
    circumference   x = 2 * (r x) * pi

instance Shape Rectangle where
    area            x = (a x) * (b x) 
    circumference   x = 2 * ((a x) + (b x) )
 
--mozemo instancirati i Circle za vec psotojecu klasu Eq tako sto sami implementiramo metod ==
--umesto da se oslanjamo na default implementaciju koju dobijamo sa deriving Eq
--tip pripada klasi Eq ako imlementira == ili !=
instance Eq Circle where
    (==) c1 c2 = (r c1) == (r c2)

-- (==) operator je mogao da stoji i infiksno u implementaciji:
instance Eq Rectangle where
    r1 == r2 = (a r1) == (a r2) && (b r1) == (b r2)

--tip pripada klasi Show ako imlementira metod show ili (? ima jos neki)
--u show pravimo string, a psoto je string [Char], mozemo da koristimo ++
instance Show Circle where
    show x = "(r=" ++ show (r x) ++ ")"

-----------------------------------------------------------------------------------------------------------------------------

class YesNo a where
    yesno :: a -> Bool

--nas nista ne sprecava da vec neki psotojeci tip npr Int, isntanciramo za neku sanu klasu
--psoto je haskel strogo tipiziran, i funkcijama mora da se prosledi argument tacno onog tipa koji
--stoji u potpisu, na ovaj nacin mozemo dobiti kao neke implicitne konverzije instanciranih tipova u Bool
instance YesNo Int where
    yesno 0 = False
    yesno _ = True
instance YesNo [a] where
    yesno [] = False
    yesno _ = True
instance YesNo Bool where
    yesno = id 
instance YesNo (Maybe a) where
    yesno Nothing = False
    yesno _       = True

--npr mozemo te konverzije da korisitmo ovako za if naredbu
yesnoIf :: (Yesno y) => y -> a -> a -> area
yesnoIf cond thenExpr elseExpr = if yesno cond then thenExpr else elseExpr
