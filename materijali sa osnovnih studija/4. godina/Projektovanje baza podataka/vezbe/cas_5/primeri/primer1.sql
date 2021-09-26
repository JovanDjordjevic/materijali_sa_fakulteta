-- demonstriranje kako se pravi baza

--ako samo ovako navedemo, ako 'vezbe' vec postoji, desice se greska
CREATE DATABASE vezbe;

-- brisemo bazu ovako
DROP DATABASE vezbe;

-- ovako nece biti prijavljena greska ako pokusamo da napravimo bazu
-- koja vec postoji
CREATE DATABASE IF NOT EXISTS vezbe;

--ovako mozemo videti definiciju baze
SHOW CREATE DATABASE vezbe;

-- kada je pokrene kod iznad, u ispisu mozmeo da vidimo da je default character set
-- stavljen da bude 'latin1'
-- to mzoemo da promenimo pri konstrukciji baze sa CHARACTER_SET
-- COLLATE je opsi kako se karakteri u setu porede (?)
CREATE DATABASE vezbe_characater_set CHARACTER_SET utf8 COLLATE utf8_bin;

SHOW CREATE DATABASE vezbe_characater_set;

-- pokretanje koda: posle -u ide username posle -p se ne navodi password, on ce biti 
-- trazen naknadno, sa < navodimo odakle se citaju sql komande
--      mysql -u jovan -p <primer1.sql