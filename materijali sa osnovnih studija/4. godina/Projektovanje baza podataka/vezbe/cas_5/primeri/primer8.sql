-- demonstriranje generisanih kolona

-- vrednosti generisanih kolona se ne cuvaju direktno, vec se izracunavaju na osnovu 
-- podataka koji su vec u bazi na osnovu nekog izraza koji odredimo
-- mozemo ih sacuvati a mozemo ih i izracunavati svaki put ponovo
USE vezbe;

DROP TABLE IF EXISTS triangle;
-- npr u tabeli za rpavougli trougao mozemo generisati vrednost za hipotenuzu
-- AS nam sluzi za opis kako se nesto genereise (pun naziv je GENERATED ALWAYS AS ali mozemo samo da pisemo AS)
-- podrazumevano ponasanje je VIRTUAL, tj genereisana kolona se ne cuva zaprano nigde 
-- vec se izracunava svaki put ponovo
CREATE TABLE triangle(
    sidea DOUBLE,
    sideb DOUBLE,
    sidec DOUBLE AS (SQRT(sidea*sidea + sideb*sideb))
);

SHOW CREATE TABLE triangle;

-- moramo da navedemo u koje tacno kolone unosimo (nisam ispratio kada moramo (?))
INSERT INTO triangle (sidea, sideb) VALUES (1,1), (3,4), (6,8);
SELECT * FROM triangle;



DROP TABLE IF EXISTS person;
CREATE TABLE person(
    first_name VARCHAR(20),
    last_name VARCHAR(20)
);

INSERT INTO person VALUES ('Mika', 'Mikic');
SELECT CONCAT(first_name, ' ', last_name) FROM person;

-- ako znamo da ce neko nad nasom tabelom raditi upite kao ovaj gore, mozemo eksplicitno
-- da navedemo kakav ce biti ispis pomocu generisanih vrednosti
-- sada smo eksplicitno naveli VIRTUAL (sto je i podrazumevano ponasanje)
DROP TABLE IF EXISTS person_generated;
CREATE TABLE person_generated(
    first_name VARCHAR(20),
    last_name VARCHAR(20),
    full_name VARCHAR(50) AS (CONCAT(first_name, ' ', last_name)) VIRTUAL
);
SHOW CREATE TABLE person_generated;

INSERT INTO person_generated (first_name, last_name) VALUES ('Mika', 'Mikic');
SELECT full_name  FROM  person_generated;
SELECT *  FROM  person_generated;


-- isto kao pre samo sto sada gledamos ta se desava kada nije VIRTUAL nego kada se cuva u tabeli
-- kljucna rec je STORED
DROP TABLE IF EXISTS person_generated_stored;
CREATE TABLE person_generated_stored(
    full_name VARCHAR(50) AS (CONCAT(first_name, ' ', last_name) ) STORED
) SELECT first_name, last_name FROM person;

SHOW CREATE TABLE person_generated_stored;

SELECT * FROM person_generated_stored;

-- pokretanje koda: 
--      mysql -u jovan -p <primer8.sql --auto-vertical-output
