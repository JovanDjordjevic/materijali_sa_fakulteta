-- demonstracija kako da se desavanja u nekoj tabeli trigeruju akciju u drugoj

USE vezbe;

-- pravimo test tabele koje su nam potrebne da bi uradili ono sto treba
DROP TABLE IF EXISTS test1;
DROP TABLE IF EXISTS test2;
DROP TABLE IF EXISTS test3;
DROP TABLE IF EXISTS test4;

CREATE TABLE test1(
    a1 INT
);

CREATE TABLE test2(
    a2 INT
);

CREATE TABLE test3(
    a3 INT NOT NULL AUTO_INCREMENT PRIMARY KEY
);

CREATE TABLE test4(
    a4 INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    b4 INT DEFAULT 0
);


-- pravimo triger koji pre unosa u test1 unosi isti podatak u test2, brise je iz test3
-- a u test4 povecava brojac b4 za a4 gde je a4 vrednost koja se unosi u a1

--treba na delimiter jer trigger ima vise instrukcija (?)
DELIMITER |

-- reminder: NEW se odnosi na polje koje se unosi
CREATE TRIGGER bi_test1
BEFORE INSERT ON test1
FOR EACH ROW 
    BEGIN
        INSERT INTO test2 SET a2 = NEW.a1;
        DELETE FROM test3 WHERE a3 = NEW.a1;
        UPDATE test4 SET b4= b4 + 1 WHERE a4 = NEW.a1;
    END;
|

DELIMITER ;


-- unesemo neke vrednosti za proveru
-- mi smo za a3 u test3 stavili da bude AUTO_INCREMENT tako da mozemo samo da unesemo
-- NULL vrednosti i da pustimo bazi da sama unese brojeve za a3
INSERT INTO test3 (a3) VALUES
    (NULL), (NULL), (NULL), (NULL), (NULL),
    (NULL), (NULL), (NULL), (NULL), (NULL)

INSERT INTO test4  VALUES
    (0), (0), (0), (0), (0),
    (0), (0), (0), (0), (0)

INSERT INTO test4 (a4) VALUES
    (2), (3), (6), (3), (5), (2), (6);


SELECT * FROM test1;
SELECT * FROM test2;
SELECT * FROM test3;
SELECT * FROM test4;
