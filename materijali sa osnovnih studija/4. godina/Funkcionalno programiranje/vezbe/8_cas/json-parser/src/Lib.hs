module Lib where

import Control.Applicative    --treba nam za sequenceA, Alternative itd
import Data.Char              --za isDigit itd

--tip koji predstavlja json vrednost (?) mala funsonta, u trecem konstruktoru imamo Integer, jer cemo 
--napraviti parser samo za brojeve (?), i radimo samo cele brojeve jer je lakse, da nebi imali gomilu provera zvbog float vrednosti
data JsonValue = JsonNull 
               | JsonBool Bool 
               | JsonNumber Integer
               | JsonString String 
               | JsonArray [JsonValue]
               | JsonObject [(String, JsonValue)]
               deriving (Show, Eq)

--pravimo parser. Hocemo da se vrati par (ostatak_inputa, parsirana_vrednost ). 
--Treba nam i MAybe za slucaj da ne uspemo lepo da parsiramo, mogli smo i Either pa da npr vrati par (br_linije, greska)
--ali ovako je jednostavnije za primer
--Do sada nismo imali pravljenje novog tipa gde je polje funkcija, do sada su bile samo vrednosti, ali
--i ovo je moguce. Funkcija/polje nam se zove runParser, da bismo iskoristili cinjenicu da haskell po defaulut
--pravi getere nasih polja koji se zovu ito kao polja 
newtype Parser a = Parser { runParser :: String -> Maybe (String, a) }



--NOTE: ovo isntanciranje smo radili tek kada stmo stigli do stringP, vidi komentare
instance Functor Parser where
    fmap f (Parser p) = Parser $ \input -> do
                                    (input', x) <- p input      --input' misli se na ostatak inputa
                                    Just (input', f x)
instance Applicative Parser where
    pure x = Parser $ \input -> Just (input, x)
    (Parser p1) <*> (Parser p2) = Parser $ \input -> do
                                                (input', f) <- p1 input
                                                (input'', x ) <- p2 input'
                                                Just (input'', f x)                                            
--NOTE: ovo isntanciranje smo radili tek kada stmo stigli do jsonBool, vidi komentare
instance Alternative Parser where
    empty = Parser $ \_ -> Nothing
    (Parser p1) <|> (Parser p2) = Parser $ \input -> p1 input <|> p2 input 



--napravii parser za uopsteni tip 'a', a hocemo da pravimo za tip JsonValue, za to su nam 
--potrebni i neki jednostavniji parseri, npr parser Char, parser Int itd

charP :: Char -> Parser Char
charP c = Parser f          --konstruisemo Parser, cije je polje ova funkcija f (?), a input 
    where f (x:xs)          --je argument funckije runParser, koji mozemo da dekonstruisemo jer je String = [Char]
            | x == c    = Just (xs, c)    
            | otherwise = Nothing
          f [] = Nothing

--Napravili smo parser koji parsira jedan karakter. Primer kako smo pozvali ovo do sad u ghci:
--  runParser (charP, 'a') "abc"      ovo vrati:     Just ("bc", 'a')
--  runParser (charP, 'b') "abc"      ovo vrati:     Nothing

--ako uradimo npr:   map charP "niska"   dobili bismo listu parsera [Parser Char], a mi bismo hteli 
--Parser [Char]  (tj Parser String). Srecom, ako smo Applicative, imamo implementiranu funkciju 
--sequenceA :: (Traversable t, Applicative f) => t (f a) -> f (t a)  koja bas radi ono sto hocem
--instancirajmo onda iznad Funcotr pa Applicatve (mora biti FUnctor da bib bio Applicative).
--NOTE: tek ovde smo pisali kod za instanciranje
stringP :: String -> Parser String
stringP input = sequenceA $ map charP input

--sada mozemo ovo, u ghci:
--  runParser (stringP, "hello") "hello world"    vraca   Just (" world", "hello")

--ako pisemo samo: jsonNull = stringP "null" dobicemo gresku, jer StringP vraca nesto sto je Parser String
--a mi hocemo da vratimo Parser JsonValue. Posto je Parser sada i Functor, mozemo sa <*> da umotamo u Parser
-- \_ je zato sto znamo da ima nesto,a  ne interesuje nas sta, a vrati JsonNull svakako (to je konstruktor pa moze)
jsonNull :: Parser JsonValue
jsonNull = (\_ -> JsonNull) <$> stringP "null"   --mozda greska u materijalima(?) instancirali smo Applicative zbog <*> a korsitimo <$>, a ako stavimo <*> ne radi

--za ovo mozemo da korsitimo <|> iz Alternative klase. NOTE: u ovom trenutku instanciramo Alternative
--Probamo da parsiramo true, ako ne moze, probamo false, ako ne moze ni to onda Nothing,
-- takodje moramo iz istog razloga kao malopre da vratimo nesto sto je oblika JsonBool 

jsonBool :: Parser JsonValue
jsonBool = fmap f $ stringP "true" <|> stringP "false"
    where f "true"  = JsonBool True
          f "false" =  JsonBool False
          f _       = undefined      --ovaj slucaj mzoemod a ostavimo undefined jer niakda nece da se desi

--primer, sada mozemo u ghci: 
--  runParser jsonBool "trueaaaa"     vrati   Just ("aaa", JsonBool True)


--pomocna funkc 
spanP :: (Char -> Bool) -> Parser String
spanP f = Parser $ \input -> let (token, rest) = span f input
                                in Just (rest, token)

--pomocna funkc
notNull :: Parser [a] -> Parser [a]
notNull (Parser p) = Parser $ \input -> do 
                                (input', xs) <- p input
                                if null xs then Nothing
                                           else Just (input', xs)                                

--funkcijom span :: (a -> Bool) -> [a] -> ([a],[a]), mozemo iz date liste (za nas String) razdvojiti brojeve i ostale karaktere
--slicno kao takeWhile, za dati predikat, span ide kroz listu i one za koje je prediakt tacan smesta
--u jednu listu, a one za koje nije u drugu. U desnoj (?) listi cemo imati String u kom su brojevi, pa treba nekako da ga konvertujemo u broj
--zbog lenjosti haskela, ako je niska brojeva prazna, izazvace nam gresku u sred racunanja, moramo
--nekako i da proerimo da li je prazna
jsonNumber :: Parser JsonValue
jsonNumber = fmap f $ notNull $ spanP isDigit
    where f ds = JsonNumber $ read ds       --read ce nam vratiti broj, od prosledjenog stringa cifara

stringLiteral :: Parser String 
stringLiteral = charP '"' *> spanP (/= '"') <* charP '"'

jsonString :: Parser JsonValue
jsonString = fmap (\s -> JsonString s) $ stringLiteral

--U ghci (primetimo da mora \" jer smo tako pisali parser):
--runParser jsonValue "\"niska\""   vrati  Just ("", JsonString "niska")    

--provera da li je white space
ws :: Parser String
ws = spanP isSpace

jsonArray :: Parser JsonValue
jsonArray fmap JsonArray $ charP '[' *> ws *> elements <* ws <* ']'
    where elements = sepBy sep jsonValue
          sep = ws *> charP ',' <* ws

--NOTE: dodajemo <|> pure [] na kraju da bi nam prolazio parser i za praznu listu
sepBy :: Parser a -> Parser b -> Parser [b] 
sepBy sep element = (:) <$> element <*> many (sep *> element) <|> pure []

--ovako izgleda json object: {"abc" : 1234 , "code" : [], ...}
jsonObject :: Parser JsonValue
jsonObject = fmap JsonObject $ charP '{' *> ws *> pairs <* ws <* '}'
    where pairs = sepBy (ws *> charP ',' <* ws) pair
          colon = ws *> charP ':' <* ws 
          pair = (\key _ valiue -> (key, value)) <$> stringLiteral <*> colon <*> jsonValue

--primer ghci:
--  runParser jsonValue "{\"key\":[1,null,{},true]}"     vrati
--  Just ("", JsonObject [{"key",JsonArray [JsonNumber 1, JsonNull, JsonObject [], JsonBool True]}])

--pravimo parser za bilo koji JsonValue
jsonValue :: Parser JsonValue
jsonValue = jsonNull <|> jsonBool <|> jsonNumber <|> jsonString <|> jsonArray


parserFile :: FilePath -> Parser a -> IO (Maybe a)
parseFile filename parser = do
    input <- readFile filename
    return snd <$> runParser parser input