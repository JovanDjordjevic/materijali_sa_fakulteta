-- demonstracija UPDATABLE i INSERTABLE za poglede

USE vezbe;

-- tabela se moze azurirati preko pogleda samo ako nedvosmisleno moze da se
-- zakljucista tacno treba da se uradi, isto i za insert

DROP TABLE IF EXISTS t1;
DROP TABLE IF EXISTS t2;

CREATE TABLE t1(
    x INT
);

CREATE TABLE t2(
    c INT
);

INSERT INTO t1 VALUES
    (2), (3), (5), (1);

INSERT INTO t2 VALUES
    (2), (3), (5), (1), (11), (11);


-- pogled sa agregatnom funkcijom
CREATE OR REPLACE VIEW v_sum
AS SELECT SUM(x) AS s FROM t1;

-- obican pogled sa poljima
CREATE OR REPLACE VIEW v_fields
AS SELECT * FROM t2;

-- pogled nad spojenim tabelama
CREATE OR REPLACE VIEW v_join
AS SELECT * FROM v_sum JOIN v_fileds ON v_sum.s = v_fields.c;

SELECT * FROM v_sum;
SELECT * FROM v_fields;
SELECT * FROM v_join;


-- ovaj insert je validan zato sto u t2 nad kojom je view napravljen
-- tacno postoji kolona c koja moze da primi int vrednost 20
INSERT INTO v_fields (c) VALUES
    (20);
-- ovaj view ce sada prikazivati i novu vrednost jer se view izracunava tek pri upitu
SELECT * FROM v_tields;

-- ovaj insert NIJE validan i nece proci zato sto se ne moze jednoznacno odrediti
-- sta treba da se insertuje i gde
-- INSERT INTO v_join (c) VALUES (1);

-- ako menjamo v_join, dozvoljeno je da menjamo c kolonu ali s kolonu ne smemo
-- zato sto je dobijena agregiranjem
UPDATE v_join SET c = c + 1;

SELECT * FROM v_sum;
SELECT * FROM v_fields;
-- priemtimo sledece, kada smo updateovali v_join, desio se update c kolone u
-- tabeli t2 nad kojojm je view napravljen. Tamo sada stoji da je c=12 sto je u redu, ali
-- sada select upit za c_join ne ispisuje nista zato sto kada proba da se izracuna
-- sadrzaj za taj view, JOIN ne moze da nadje nista sto moze da spoji i rezultat
-- je prazna tabela
SELECT * FROM v_join;

-- ovo nece proci, dobicemo gresku da nije updatable
-- UPDATE v_join SET s = s + 1;

-- pre brisanja
SELECT * FROM t2;
-- brisanje vrednosti kroz view moze da se radi pod istim uslovima kao insert i update
-- tj kada je jano sta treba da se desi
-- ovo je validno
DELETE FROM v_fields WHERE c = 12;
-- posle brisanja
SELECT * FROM t2;


-- ako view ima neku kosntantu kao sto je ovde col2, ona ne moze da se updatuje
-- ali ova obicna kolona c ce moci 
CREATE OR REPLACE VIEW v
AS SELECT c AS col1, 1 AS col2 FROM t2;

SELECT * FROM v;

-- ovo prolazi
UPDATE v SET col1 = 0;
SELECT * FROM t2;

-- ovo ne prolazi
-- UPDATE v SET col2 = 2;

-- pokretanje:
-- mysql -u jovan -p <primer2.sql