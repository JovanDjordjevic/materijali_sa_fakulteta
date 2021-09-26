-- demonstriranje kreiranja tabele

-- da bismo korsitili neku bazu koja vec postoji (npr 'vezbe' iz proslog primera)
-- naovidmo je sa USE
USE vezbe;

-- NOTE: posto rad sa bazama generalno podatke upisuje na disk, a ne u RAM, svako
-- naknadno pokretanje istog koda barata sa podacima koji mozda vec postoje na disku
-- dakle ako nebi naveli ovo DROP TABLE prvo, prvi put kada pokrenemo primer2 bila
-- bi lepo napravljena tabela, ali pri sledecem pokretanju bila bi prijavljena greska
-- jer t vec postoji. Generalno o ovome moramo da vodimo racuna i za tabele
-- i za same baze
DROP TABLE IF EXISTS t;

CREATE TABLE t(
    a CHAR(20),
    b CHAR(20)
);

-- ovako mozemo videti definiciju tabele
SHOW CREATE TABLE t;



DROP TABLE IF EXISTS t_column_constraint;

CREATE TABLE t_column_constraint(
    a CHAR(20) CHARACTER SET utf8 COLLATE utf8_bin, -- mozemo pojedinacno da menjamo charset za neki konkretan
                                                    -- podatak, bez da menjamo charset cele tabele
    b char(20)
);

SHOW CREATE TABLE t_column_constraint;



DROP TABLE IF EXISTS t_table_constraint;

CREATE TABLE t_table_constraint(
    a CHAR(20) CHARACTER SET utf8 COLLATE utf8_bin,
    b char(20)
) CHARACTER SET utf8 COLLATE utf8_bin;  --a ovako menjamo charset tabele

SHOW CREATE TABLE t_table_constraint;


-- pokretanje koda: (kada pokrenemo bez --auto-vertical-output opcije, ne bude 
-- lep ispis kao sto bi ocekivali)
--      mysql -u jovan -p <primer2.sql --auto-vertical-output
