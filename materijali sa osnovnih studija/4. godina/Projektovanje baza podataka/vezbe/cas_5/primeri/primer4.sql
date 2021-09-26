-- demonstriranje kako se koriste indeksi
-- indeksi sluze da se sacuva poredak podataka (?) da bi pretraga bila brza (?)
-- kada se azurira neki podatak u bazi, mora se azurirati i u indeksu
-- dakle kada imamo dosta izmena u bazi, ovo je sporije nego kada nemamo indekse, 
-- ali kada imamo dosta upita/pretraga, rad sa indeksima je bolji pristup

USE vezbe;


-- imamo vise nacina za pravljenje indeksa, ovo je jedan od njih. 
-- Mozemo navesti i da li hocemo BTREE ili HASH ineks (u zavisnosti sta ENGINE koji
-- koristimo dozvoljava) (Podrazumevani je InnoDB koji dozvoljava samo B stabla)
-- sintaksa (za ovaj nacin) je:
--      INDEX 'ime_indeksa' [USING {BTREE | HASH}] (ime_atributa_koji_indeksiramo)
CREATE TABLE lookup(
    id INT,
    name VARCHAR(20),
    INDEX ind_name USING BTREE (name)   
) ENGINE = MEMORY;

SHOW CREATE TABLE lookup;


-- brisanje indeksa
ALTER TABLE lookup DROP INDEX ind_name;
SHOW CREATE TABLE lookup;

-- prosli nacin je bio pravljenje indeksa tokom pravljenja same tabele
-- ali indeks mozemo da pravimo i nakdnadno
-- uz atribut nad kojim pravimo indeks mozemo navesti i duzinu koja se indeksira
-- npr u nasoj tabeli name je niska od 20 karaktera, ali mozemo da indeksiramo
-- name(10) tj samo prvih 10
-- pod uslovom da engine podrzava, mozemo pormeniti u HASH (zato smo u liniji 19 stavili
-- MEMORY iako smo koristili BTREE koji imamo u podrazumevanom engine-u) 
CREATE INDEX ind_name ON lookup (name(10)) USING HASH;

-- pokretanje koda: 
--      mysql -u jovan -p <primer4.sql --auto-vertical-output
