module Lib where

--pravimo neku kao biblioteku za window manager. Imamo nekekakve prozore i hocemo da implementiramo 
--da se oni menjaju na alt-tab, otvaraju, zatvaraju it.Na pocetku smo prozore tretirali kao obicnu listu integera
--nakon toga smo uveli nas tip Ring, i uveli taj tip u potpise funkcija

--type u haskelu je slicno kao using iz c+
    --type Ring a = [a]

--ako radimo samo sa type, haskel ce dozvoljavati implicitnu konverziju ako je moguce, jer je to u sustini samo alias
--tj. ako samo svugde gde je stajalo [a] stavimo Ring a, za sada ce sve raditi kako treba
--ako hocemo da sprecimo to, moramo da koristimo newType kljucnu rec. Pritom, moramo da napravimo i konstruktor
newType Ring a = MkRing [a]

fromList :: [a] -> Ring a
fromList = MkRing

--posto je Ring a = MkRing [a], mzemo na taj nacin da ga dekonstruisemo
toList :: Ring a -> [a]
toList (MkRing ws) = ws


--neka otvaranje prozora bude samo dodavanje u listu na pocetak
openWindow :: a -> Ring a -> Ring a
openWindow w (MkRing ws) = MkRing (w:ws)

--zatvaranje neka bude izbacivanje iz litse 
--mozemo nekom izrazu dati spec. ime i onda da ga koristimo dalje u toj funkciji:   ime@izraz
closeWindow :: Ring a -> Ring a
closeWindow r@(MkRing []) = r                --isto kao da pise:   closeWindow (MkRing []) = MkRing []
closeWindow (MkRing ws) = MkRing (tail ws)

--neka menjanje aktivnog bude samo zamena mesta prvom i drugom clanu
--listu mozemo dekomponovati i na vise od (a:b), npr (a:b:c:d:e...)
switchActive :: Ring a -> Ring a
switchActive r@(MkRing []) = r
switchActive r@(MkRing [w]) = r
switchActive (MkRing (active:next:others)) = MkRing (next:active:others)

--focusNext je malo komplikovaniji od switchActive jer ovde idemo redom kroz celu listu 
--prozora, a ne menjemao mesa prva dva prozora u listi kao u switchActive
--NOTE: ubacivanje elementa na pocetak moze sa x:xs, ali ne moze na kraj ( xs:x) vec ako hocemo na kraj
--moramo npr xs ++ [x], primeti da ++ spaja liste, a posto je x jedan element, mora eksplicitno da se navede 
--da je u pitanju lista sa [x]
focusNext :: Ring a -> Ring a
focusNext r@(MkRing []) = r
focusNext (MkRing (w:ws)) = MkRing (ws ++ [w])

--NOTE: na vezbama nije prepravio ovu funkciju za MkRing, ostavio ju je undefined
--Ne moze da se koristi kompozicija funkcija u tom slucaju (?)
--moglo je i jednostavnije da se napise ova funkc, ali on je hteo da pokaze primer za kompoziciju
--      focusPrev :: Ring a -> Ring a
--      focusPrev ws = reverse $ focusNext $ reverse ws
--moglo je skracenije da se zapise u point free zapisu (gde funkciju zapisemo kao kompoziciju
--funckija, bez navodjenja argumenata):
--      focusPrev = reverse . focusNext . reverse



----------------------------------------------------------------------------------------------------------------
--isti primer samo sa daljom optimizacijom, gde listu prozora cuvamo u dve liste. Ima lepo u zvanicnim materijalima
--ovo moje mozda nece moci da se porkece zbog duplih istih funkcija
-------------------------------------------------------------------------------------------------

--data je slicno kao newType samo sto nam omogucava da imamo vise konstruktora i atributa koji ima nas tip (ali je zato manje efkasno od newtype)
--haskel prikazuje objekte takos to pozove funkciju show(), on funkcionise za integere, liste itd, ali ne funkcionise za nase tipove
--to mozemo da popravimo ako kazemo da nas tip nasledjuje tip Show, onda ce dobiti neku default implementaciju
--ta implementacija je takva da ispise konstruktor i oba polja (levu i desnu listu)
--mogli smo i sami da navedemo kako ce izgledati metod show za nas tip
data Ring a = MkRing [a] [a] deriving Show

fromList :: [a] -> Ring a
fromList ws = MkRing ws []

toList :: Ring a -> [a]
toList (MkRing ls rs) = ls ++ (reverse rs)

openWindow :: a -> Ring a -> Ring a
openWindow w (MkRing ls rs) = MkRing (w:ls) rs

closeWindow :: Ring a -> Ring a
closeWindow (MkRing [] []) = MkRing [] []
closeWindow (MkRing [w] rs) = MkRing (reverse rs) []
closeWindow (MkRing (_:ls) rs) = MkRing ls rs

switchActive :: Ring a -> Ring a
switchActive (MkRing [] []) = MkRing [] []
switchActive (MkRing [w] []) = MkRing [w] []
switchActive (MkRing [w] rs) = switchActive $ MkRing (w:(reverse rs)) []
switchActive (MkRing active:others:others rs) = MkRing (next:active:others) rs

focusNext :: Ring a -> Ring a
focusNext (MkRing [] []) = MkRing [] []
focusNext (MkRing [w] rs) = focusNext $ MkRing(w:(reverse rs)) []
focusNext (MkRing (l:ls) rs) = MkRing ls (l:rs)

focusPrev :: Ring a -> Ring a
focusPrev (MkRing [] []) = MkRing [] []
focusPrev (MkRing ls []) = focusPrev $ MkRing [] (reverse ls)
fromPrev (MkRing ls (r:rs)) = MkRing (r:ls) rs