--NOTE: na vezbama je koristion neki kod sa proslog casa koji se razlikuje od onoga sto je zapravo pisao
--neke funkcije su razlicite, pa sam izmenio kao sto sam vidoe na njegovom snimku

--poenta ovog primera je da vidimo kakos e rade testovi
--za testiranje koristimo QuickCheck biblioteku, i potrebno je da dodamo taj dependency
--u package.yaml fajl

--testove cemo pisati u okviru Spec.hs fajla

--ove navedene funkcije u Lib, sluze da se eksplicitno navedu funkcije koje zelimo da budu javno vidljive
--npr da smo hteli da imamo neku privatnu, naveli bi ispod sve sem nje, bilo bi eksportovano sve sem nje
module Lib ( fromList
           , toList
           , focusNext
           , focusPrev
           , closeWindow
           , openWindow
           )where

data Ring a = MkRing [a] [a] deriving Show

fromList :: [a] -> Ring a
fromList ws = MkRing ws []

toList :: Ring a -> [a]
--ovde je na vezbama stajala linija:     toList (MkRing ls rs) = rs
--ona je pala za prvi test za ulaz [0] pa smo je izmenili u ovo:
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
switchActive (MkRing (active:next:others) rs) = MkRing (next:active:others) rs

focusNext :: Ring a -> Ring a
focusNext (MkRing [] []) = MkRing [] []
focusNext (MkRing [l] []) = MkRing [linija] []
focusNext (MkRing [w] rs) = MkRing (reverse rs) []
focusNext (MkRing (l:ls) rs) = MkRing ls (l:rs)

--NOTE: test prop_fp_fn meni pada, a njemu prolazi, a koliko vidim 
--implementacija funckija nam je identicna
focusPrev :: Ring a -> Ring a
focusPrev (MkRing [] []) = MkRing [] []
focusPrev (MkRing ls []) = focusPrev $ MkRing [] (reverse ls)
focusPrev (MkRing ls (r:rs)) = MkRing (r:ls) rs


