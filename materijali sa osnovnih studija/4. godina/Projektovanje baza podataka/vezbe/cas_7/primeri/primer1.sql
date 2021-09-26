-- demonstracija pravljenja pogleda

-- pretpostavimo da mozemo da korsitimo bazu 'vezbe' od ranije
USE vezbe;

-- ako pogled ne postoji mozemo da korsitimo samo CREATE, a ako postoji
-- mozmeo i OR REPLACE
-- pogled koji napravimo ne mora uopste da referie na neku postojecu tabelu
-- npr ovde samo uzimamo CURRENT_DATE (to je ugradjena promenljiva (?))
CREATE OR REPLACE VIEW v_today(
    today
) AS SELECT CURRENT_DATE;

SELECT * FROM v_today;


DROP TABLE IF EXISTS t;
CREATE TABLE t(
    qty INT,
    price INT
);


-- ovako mozemo da napravimo view koji izvlaci podatke iz neke vec postojece tabele
CREATE OR REPLACE VIEW v
AS SELECT * FROM t;

INSERT INTO t VALUES (3, 50);
-- kada smo definisali pogled iznad, mi u tom trenutku nismo zapravo izracunali 
-- podatke koji treba da se prikazu, to se desava tek kada postavimo upit posle toga
-- tj ovde
SELECT * FROM v;


-- view naravno moze imati i kolone koje ne postoje direktno u tabeli
CREATE OR REPLACE VIEW v_today
AS SELECT qty, price, qty*price AS value FROM t;
-- i kada pokrenemo upit to se izracuna i prikaze
SELECT * FROM v;


-- pokretanje:
-- mysql -u jovan -p <primer1.sql