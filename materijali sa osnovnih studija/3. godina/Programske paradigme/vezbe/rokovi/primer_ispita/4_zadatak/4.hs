data Transakcija = MkTransakcija{
                     ident :: Int,
                     iznos :: Int,  
                     posiljalac :: String,
                     primalac :: String
                   } deriving (Show, Eq)

type AktivneTransakcije = [Transakcija]

izlistaj :: AktivneTransakcije -> String -> [Transakcija]
izlistaj ts br = filter (\t -> ((primalac t) == br) || ((posiljalac t) == br) ) ts

dodaj :: AktivneTransakcije -> Transakcija -> AktivneTransakcije
dodaj ts t = t : ts

ukloni :: AktivneTransakcije -> Int -> AktivneTransakcije
ukloni ts iden = filter (\t -> (ident t) /= iden) ts

ukupno :: AktivneTransakcije -> Int
ukupno ts = foldl (\acc t -> acc + (iznos t)) 0 ts

{-
let t = MkTransakcija 0 600 "p5" "p4"

let t1 = MkTransakcija 1 200 "p1" "p2"
let t2 = MkTransakcija 2 209 "p1" "p3"
let t3 = MkTransakcija 3 110 "p2" "p1"
let t4 = MkTransakcija 4 123 "p3" "p2"
let t5 = MkTransakcija 5 501 "p3" "p4"


let b = [t1, t2, t3, t4, t5]
-}