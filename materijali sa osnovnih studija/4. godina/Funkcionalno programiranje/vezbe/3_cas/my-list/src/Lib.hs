module Lib where

--nasa implementacija haskell liste

--NOTE: ovo je bila prva implementacija
-- --data moze imati vise konstruktora, npr napravili smo ovde konstruktor za praznu listu i konstruktor
-- --koji se sastoji od glave i repa liste
-- --U haskelu je skroz okej da referisemo na MyList tip u okviru konstruktora
-- data MyList a = Empty
--               | Cons a (MyList a) 
--               deriving Show

-- listConcat :: MyList a -> MyList a -> MyList a
-- listConcat Empty rs = rs                                --leva lista prazna, desna nije
-- listConcat (Cons l Empty) rs = Cons l rs                --leva ima samo jedan element
-- listConcat (Cons l ls) rs = Cons l (listConcat ls rs)   --leva moze da se dekonstruise na glavu i rep

--druga implementacija:
--ovde u konstruktoru pravimo operator :/: i hocemo da bude desno asocijativan sa prioritetom 7
--da smo hteli levu asoc, pisali bi infixl. 7 smo stavili odokativno, postoji tabela prioriteta u haskelu
infixr 7 :/:
data MyList a = End
              | (:/:) a (MyList a)
--sa ovakvim tipom mozemo u ghci da pravimo listu npr ovako:  3 :/: End, ili npr 1 :/: 2 :/: 3 ,sto lici na ++ i : sto smo i hteli

--nije dovoljno da pise samo instance Show (MyList a) where ,zato sto pozivamo ispod show x, a nigde nemamo
--garanciju da to x ima implementiran show metod. Zato moramo da naglasimo da 'a' pripada klasi Show
--slicno kao kad pisemo funkcije 
instance Show a => Show (MyList a) where
    show lst = "[" ++ show' lst ++ "]"

show' :: Show a => MyList a -> String
show' End = ""
show' (x :/: End) = show x                      --pazi u ove dve linije kad je je show a kad je show'
show' (x :/: xs) = show x ++ " " ++ (show' xs)  --jer hocmeo da dobijemo ispis oblika [1 2 3]


--hocmeo da napravimo infiksni operator slican ++ koji spaja nase liste
--mozemo i u pattern matchingu da koristimo infiksno
infix 6 +/+
(+/+) :: MyList a -> MyList a -> MyList a
End         +/+ rs = rs
(l :/: End) +/+ rs = l :/: rs
(l :/: ls)  +/+ rs = l :/: (ls +/+ rs)


--hocemo da za nasu lsitu napravimo nesto slicno map funkciji, ali map radi samo za liste
--psotoji funkcija fmap, koja je kao genericka map funkcija koja radi za sve tipove koji
--instanciiraju klasu Functor (dovoljno je da se implementira fmap), pogledaj potpis za fmap u interpreteru

--primetimo da je ovde instnaciranje malo drugacije, ne pisemo (MyList a) kao za npr Show (objasnce na sledecem casu)
instance Functor MyList where
    fmap f End = End
    fmap f (x :/: xs) = (f x) :/: (fmap f xs)

--hocemo i da napravimo implementaciju za fold. Primetimo da je opet samo MyList umesto (MyList a)
instance Foldable MyList where
    foldr f init End = init
    foldr f init (x:/:xs) = f x (foldr f init xs)  --pazimo redosled ovde jer hocemo foldr