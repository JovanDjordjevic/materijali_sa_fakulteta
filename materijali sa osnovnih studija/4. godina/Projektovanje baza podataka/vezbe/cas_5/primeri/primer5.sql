-- demonstriranje ogranicenje za priamrni kljuc

-- NOTE: kada je nesto primarni kljuc on sigurno ne sme biti null,
-- cak iako ne navedemo to sami, baza ce za nas to uraditi, tj postavice da ne bude null

USE vezbe;

DROP TABLE IF EXISTS lookup;
-- imamo nekoliko nacina za ovo, npr ovde navoidmo to kao ogranicenje atributa
CREATE TABLE lookup(
    id INT PRIMARY KEY,
    name VARCHAR(20)
);
SHOW CREATE TABLE lookup;


DROP TABLE IF EXISTS lookup2;
-- moze i ovako (NOTE: ovo je jedini nacin da se oznaci primarni kljuc ako se on sastoji
-- od vise od jednog atributa)
CREATE TABLE lookup2(
    id INT,
    name VARCHAR(20),
    PRIMARY KEY (id)
);
SHOW CREATE TABLE lookup2;


DROP TABLE IF EXISTS lookup3;
CREATE TABLE lookup3(
    id INT,
    name VARCHAR(20),
    PRIMARY KEY (id, name)    -- ovako
);
SHOW CREATE TABLE lookup3;


-- brisanje primarnog kljuca
ALTER TABLE lookup3 DROP PRIMARY KEY;
SHOW CREATE TABLE lookup3;

-- naknadno dodavanje primarnog kljuca
-- ako ovo radimo moramo sa add constraint, sintaksa je
--      ADD CONSTRAINT 'ime_constrainta' ...
ALTER TABLE lookup3 ADD CONSTRAINT pk_id PRIMARY KEY (id);
SHOW CREATE TABLE lookup3;

-- pokretanje koda: 
--      mysql -u jovan -p <primer5.sql --auto-vertical-output
