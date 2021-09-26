-- demonstriranje nekoliko masina za skladistenje
USE vezbe;

-- ovako ispisujemo sve moguce masine za skladistenje, podrazumevana je
-- InnoDB koja podrzava transakcije, zakljucavanje i strane kljuceve, ali ima
-- ih raznih, vidi na slajdovima sta koja moze
SHOW ENGINES;

DROP TABLE IF EXISTS t_innodb;
CREATE TABLE t_innodb(
    i INT
) ENGINE = INNODB;   -- ovako za tabelu navodimo koji engine za skladistenje koristi


DROP TABLE IF EXISTS t_csv;
CREATE TABLE t_csv(
    i INT NOT NULL  --ovako za neki atribut navodimo da ne sme da ima null vrednost
                    -- CSV masina zahteva da ne smemo imati null, ako poreknemo bez ovoga
                    -- videli bismo gresku
) ENGINE = CSV;


DROP TABLE IF EXISTS t_memory;
CREATE TABLE t_memory(
    i INT 
) ENGINE = MEMORY;

--pogledamo kakav nam ispis ovo daje
SHOW CREATE TABLE t_innodb;
SHOW CREATE TABLE t_csv;
SHOW CREATE TABLE t_memory;

-- pokretanje koda: 
--      mysql -u jovan -p <primer3.sql --auto-vertical-output
