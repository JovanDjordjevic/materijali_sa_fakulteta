module Zad1 where


-- Zadatak 1:
--
-- Definisati tip podataka `Point2D` koji se može konstruisati 
-- putem konstruktora `MkPoint2D` i koji se sastoji od atributa:
--  * `x` (tipa `Double`) koje predstavlja x-koordinatu tačke 
--  * `y` (tipa `Double`) koje predstavlja y-koordinatu tačke 

data Point2D = MkPoint2D {x :: Double, y :: Double} deriving (Show, Eq)
--
-- Definisati tip podataka `Rectangle` koji se može konstruisati 
-- putem konstruktora `MkRectangle` i koji se sastoji od atributa:
--  * `bott_left` (tipa `Point2D`) koje predstavlja teme A pravougaonika 
--  * `top_right` (tipa `Point2D`) koje predstavlja teme C pravougaonika
-- (pretpostaviti da su stranice pravougaonika paralelene koordinatnim osama)
--
--             D     (C)
--
--            (A)     B

data Rectangle = MkRectangle {bott_left :: Point2D, top_right :: Point2D} deriving (Show, Eq)

--
-- Definisati klasu `Traversible a` koja sadrži funkciju
-- `traverse :: a -> [Point2D]`

class Traversible a where
    traverse :: a -> [Point2D]

--
-- Instancirati `Traversible` za `Rectangle` tako da funkcija `traverse`
-- vrati listu [A,B,C,D]
--

instance Traversible Rectangle where
    traverse r = [bl r, br r, tr r, tl r]
        where bl r = bott_left r                                       -- A
              br r = MkPoint2D (x (top_right r)) (y (bott_left r))     -- B
              tr r = top_right r                                       -- C
              tl r = MkPoint2D (x (bott_left r)) (y (top_right r))     -- D


-- Definisati funkciju `rotTrans rect` koja rotira pravougaonik za 90 stepeni
-- u smeru kazaljke na satu ali tako da teme B dođe na mesto temena A 
-- (kao na slici ispod) i vraća dobijeni pravougaonik:
--
--            | D     (C)         | A   (D)
--            |             ->    |
--            |(A)     B          |(B)   C
--            ````````````        ``````````

rotTrans :: Rectangle -> Rectangle
rotTrans r = MkRectangle b d
    where b = MkPoint2D (x (top_right r)) (y (bott_left r))
          d = MkPoint2D (x (bott_left r)) (y (top_right r))

--
-- Napisati QuickCheck test koji testira funkciju `rotTrans`. 
-- Pomoc: Iskoristiti činjenicu da dva puta primenjena rotacija na ovakav
--        nacin predstavlja identitet.

prop_doubleRot r =
    r == (rotTrans $ rotTrans r)
    where types = (r :: Rectangle)