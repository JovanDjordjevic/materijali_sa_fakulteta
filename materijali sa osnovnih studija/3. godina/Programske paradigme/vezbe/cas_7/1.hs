--trebace nam kasnije funkcija elemIndex iz modula Data.List, uvodimo alias as List
--ako nam ne treba ceo modul vec neki njegov specifican deo stavimo to u zagradu
import Data.List as List (elemIndex, sortBy)
import Data.Maybe as DM


--ako zelimo neki komplikovaniji tip od ono sto smo radili prosli cas radimo to sa kljucnom reci data
--ovo Osnovne, Master itd su KONSTRUKTORI (dakle nas "objekat" StepenStudije bice ono sto vrati jedan od tri moguca konstruktora), 
--ali ako samo probamo da tako pozovemo u ghci npr OsnovneStudije prijavice se greska, 
--a to je da taj kontruktor ne implementira print funckiju iz klase Show (?)
--zato na kraju dodamo za nas tip ovo "deriving Show" da bi se implementirao neki default print
--tj u ovom slucaju ono sto ce se ispisati je samo ime funkcije OsovneStudije
--ako hocemo da nasledjujemo jos neku klasu, npr Eq za poredjenje, moramo to ovako u zagradama
--moze sve u jednom redu ali ovako je lepse posebno ako imamo vise argumenata u kotsruktoru
data StepenStudija = OsnovneStudije 
                   | MasterStudije 
                   | DoktorskeStudije 
                   deriving (Show, Eq)

--hocemo da nam se npr MasterStudija prikaze u kracem zapisu MSc, pravimo novi tip koji sad ima konstruktor
--a taj kontruktor ima kao argument onaj nas tip iznad. Ovog puta ne radimo "deriving Show" jer hocemo sami da napravimo neki ispis
data KratkiStepenStudija = Kratko StepenStudija
--kazemo da je KratkiStepenStudija instanca klase Show, ali da bi to radilo ona mora da implementira metod show
instance Show KratkiStepenStudija where
    --ako pogledamo :t show vidimo da prima bilo sta i vraca string, Show a => a->String
    --i ovde nam je lako samo da za sve tri mogucnosti kazemo kako ce se ova funkcija odvijati, ako smo hteli da standardno poredimo sa if ==
    --morali bismo gore da stavimo "deriving Eq"  iza Kratko StepenStudija
    show (Kratko OsnovneStudije) = "BSc"
    show (Kratko MasterStudije) = "MSc"
    show (Kratko DoktorskeStudije) = "PhD"
    --ako hocemo jos neki slucaj koji bi hipoteticki obuhvatao sve ostalo, dodali bismo izraz sa wildcardom ispod:
    --show (Kratko _) = ...

--ako bismo hteli da napravimo tip Student na osnovu ovoga sto smo pisali iznad ovako bi izgledalo:
--data Student = MkStudent String String StepenStudija
--ali tu se sad ne zna sta je koji od argumentata, nnpr vidimo da su String String ali ne znamo da li je ime pa prezime ili prezime pa ime
--zato u {} zagradama uvodimo imena za parametre, NE ZABORAVI ZAREZ!!!!
--primeti da su indeks,ime itd takodje GETERI za ova polja iz naseg Studenta (posto su funkcije, jer je u haskelu sve funkcija(?))
--takodje zbog tog razloga one moraju biti jedinstvenog imena na globalnom nivou!
--takodje posto je sve u haskelu IMUTABILNO, ne mozemo jednom napravljemom studentu promeniti neko polje
data Student = MkStudent { indeks :: String
                         , ime :: String
                         , prezime :: String
                         , stepen :: StepenStudija
                         }

formatirajStudenta :: Student ->String
formatirajStudenta s = 
    let id = indeks s
        ip = (ime s) ++ " " ++ (prezime s)
        ss = show $ Kratko $ stepen s  --ovde mora show zato sto u haskelu nema implicitne konverzije u stirng, Kratko (stepen s) nece sam pos ebi vratiti string tako da nebismo mogli u izrazu ispod da radimo  ++ sa tim
    in id ++ " : " ++ ip ++ " : " ++ ss
    --ova funkc dodje kao neki toString, mogli smo standardno sa where id =.. ip =.., ovo je samo jos jedan nacin da se to uradi

instance Show Student where
    show s = formatirajStudenta s

--da bi bila isntanca Eq mora da implementira funkciju ==
instance Eq Student where
    --psoto je == infiksni mozemo da pisemo ovako, a mogli smo i kao do sada prefiksno sa: (==) s1 s2 =...
    --posto radimo samo poredjenje po indeksu mozemo sa vec postojecim == zato sto su stringovi vec u klasi Eq
    --da smo npr hteli da radimo poredjenje po stepenus tudija to nebi proslo ako on nije u Eq
    s1 == s2 = (indeks s1) == (indeks s2)

--zelimo da za svakog studenta cuvmao njegove poene na ispitu, ali moze se desiti da nekis tudenti npr nisu izasli ili izasli pa ponistili itd
--zato umesto da koristimos pecijalne vrednosti (npr -1, -2 itd) koristimo tip Maybe, koji kaze da na tom mestu moze a i ne mora da se nadje neka vrednost
--data Maybe a = Nothing | Just a 
type Rezultat = (Student, Maybe Int)

rezultati :: [Student]->[Rezultat]
rezultati studenti = map (\s-> (s,Nothing)) studenti

--Either koristimo za situacije kada mzoe da se vrati jedna od dve stvari (?)
--data Either a b = Left a | Right b
--ovde smo uveli to za specijalan slucaj kada se trazi podatak o poenima za studenta koji nije u listi
--konvencija je da u Either levo ide to sto je izuzetak (za nas string) a desno ono sto je norma (za nas ovde Maybe Int)
poeni :: Student->[Rezultat]->Either String (Maybe Int)
poeni s rez = 
    --moglo je i standardno if .. then .., posto elemIndex vraca Maybe Int, moguci rezultati su Nothing i (Just x) tako da je to ono sto stavljamo u case
    case mi of Nothing -> Left $ (indeks s) ++ "se ne nalazi u listi"    --treba nam Left da bi se naznacilo da vracamo levus tavku iz Either
               (Just i)-> Right $ snd (rez !! i)       
    where mi = List.elemIndex s (map fst rez)      --elemIndex je funkcija iz Data.List, ona vraca poziciju trazenog elementa u listi ako on postoji ili Nothing (znaci vraca Maybe Int)
                                                 --posto trazimo Student moramo od nase [Rezultat] napraviti [Student], to samo radimo mapiranje fst

--moglo je i foldl, ovo je smao za primer
ponisti :: Student->[Rezultat]->[Rezultat]
ponisti s rez = foldr azuriraj [] rez
    where azuriraj r acc = if (fst r) == s then (s, Nothing) : acc
                                           else r : acc

ponistiSve :: [Rezultat]->[Rezultat]
ponistiSve rez = map (\r->(fst r, Nothing)) rez 

studije :: StepenStudija->[Rezultat]->[Rezultat]
studije ss rez = filter (\r -> stepen (fst r) == ss ) rez

polozeni :: [Rezultat]->[Rezultat]
--ovde u lambda funkc nismo smeli mozdaRez > 50 zato sto je to mozdaRez Maybe Int, a on je ili Nothing ili Just Int, a Just Int ne moze da se poredi sa Int
polozeni rez = filter (\(s, mozdaRez) -> (izvuci mozdaRez) > 50) rez
    where izvuci Nothing = 0
          izvuci (Just poeni) = poeni

upisi :: Student->Int->[Rezultat]->[Rezultat]
upisi s p rez = if elem s studenti 
                then foldr azuriraj [] rez
                else (s, Just p) : rez
    where studenti = map fst rez
          azuriraj r acc = if fst r == s then (s,Just p) : acc
                                         else r : acc

najboljih :: Int -> [Rezultat]->[Int]
najboljih n rezultati = take n                       --uzimamo n
                    $ List.sortBy (flip compare)     --sortBy prima funkciju po kojoj sortira i listu, ovde smo za tu funkc vec koristili ugradjenu funkciju comapre, flip je za obrnuti poredak (?) 
                    $ map DM.fromJust                --ugradjena funck koja od maybe int pravi int (ona radi isto ono sto smo rucno pisali u pomocnoj funkc "izvuci")
                    $ filter (\x -> x /= Nothing)    --one koji nisu nul
                    $ map snd                        --izvlacimo samo poene
                    $ rezultati                 


---------------------------------------------------------------------------------