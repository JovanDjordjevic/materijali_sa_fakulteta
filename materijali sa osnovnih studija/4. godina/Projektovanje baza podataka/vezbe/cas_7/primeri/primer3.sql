-- demonstracija WITH CHECK OPTION

-- ako zelimo da azuriramo podatke koji u tabeli koji nisu direktno obuhvaceni pogledom 
-- tada ne stavljamo WITH CHECK OPTION, a kada zelimo da moze da se updatuje
-- samo ono sto jeste obuhvaceno pogledom onda cemo da stavimo WITH CHECK OPTION

-- kada definisemo pogled nad pogledom, taj novi pogled ce sam da zakljuci da
-- li je izmena dozvoljena ili ne (?)

USE vezbe;

DROP TABLE IF EXISTS t;
CREATE TABLE t(
    a INT
);

INSERT INTO t VALUES
    (0), (1), (2), (3), (4), (5);

-- obican pogled
CREATE OR REPLACE VIEW v_no_check_option
AS SELECT * FROM t WHERE a < 2;

-- ovo je validno
INSERT INTO v_no_check_option VALUES
    (6);

-- iako se 6 nece videti u pogledu jer je 6>2, videce se u tabeli
SELECT * FROM v_no_check_option;
SELECT * from t;



CREATE OR REPLACE VIEW v_with_check_option
AS SELECT * FROM t WHERE a < 2;
WITH CHECK OPTION;

-- posto sada imamo WITH CHECK OPTION, ako pokusamo da unesemo neki podatak
-- u view (tj u izvornu tabelu preko view-a) koji ne zadovoljava uslov iz pogleda
-- to nece biti dozvoljeno
-- INSERT INTO v_with_check_option VALUES
--    (7);
-- SELECT * FROM v_with_check_option;
-- SELECT * from t;


-- pogled nad pogledom, imamo WITH LOCAL CHECK OPTION i WITH CASCADE CHECK OPTION   
-- local proverava samo za pocetni pogled, a cascade ce da proverava za sve pogleda
-- nad kojima je pocetni definisan

-- ovaj pogled ce proveravati samo za a>0  a ignorisace uslov a<2 iz v_no_check_option
CREATE OR REPLACE VIEW v_with_local_check_option
AS SELECT * FROM v_no_check_option where a > 0
WITH LOCAL CHECK OPTION;

-- ovde ce biti uvazeni i uslovi a>0 i a<2 iako v_no_check nema check option (?)
CREATE OR REPLACE VIEW v_with_cascade_check_option
AS SELECT * FROM v_no_check_option where a > 0
WITH CASCADE CHECK OPTION;

-- ovo ne prolazi zato sto mora a>0
--  INSERT INTO v_with_local_check_option VALUES (-10);

--ovo prolazi
INSERT INTO v_with_local_check_option VALUES (10);
SELECT * FROM t;

-- ovo ne moze
--  INSERT INTO v_with_cascade_check_option VALUES (-10);
-- ne moze ni ovo, zato sto proveravamo kaskadno
--  INSERT INTO v_with_cascade_check_option VALUES (10);
-- ali ovo moze
INSERT INTO v_with_cascade_check_option VALUES (1);
SELECT * FROM t;


-- pokretanje:
-- mysql -u jovan -p <primer3.sql