-- demonstriranje dodatnog nacina pravljenja tabela
-- tj pravljenja pomocu LIKE i pomocu SELECT

USE vezbe;

DROP TABLE IF EXISTS new_child;

-- ovako pravimo tabelu koja je ista kao neka vec postojeca (child iz proslog primera)
CREATE TABLE new_child LIKE child;
SHOW CREATE TABLE new_child;

-- pravimo neku tmp tabelu foo da bismo mogli da kreiramo novu tabelu sa SELECT ispod
DROP TABLE IF EXISTS foo;
CREATE TABLE foo(
    n INT NOT NULL
);

INSERT INTO foo VALUES(1);

SELECT * FROM foo;

-- hocemo da napravimo neku tabelu koja ima kolone iz tabele foo plus neku svoju
-- dodatnu kolonu. Kada ovo napravimo, ne samo da ce bar naslediti kolonu n iz foo
-- nego ce naslediti i sve podatke iz te kolone, to mozemo da vidimo u ispisu 
-- SELECT upita ispod
-- (naravno ova naredba ne proalzi ako nije moguce da se kolona n izdvoji iz foo)
DROP TABLE IF EXISTS bar;

CREATE TABLE bar(
    m INT
) SELECT n FROM foo;

SHOW CREATE TABLE bar;

SELECT * FROM bar;


-- postavljanje UNIQUE ogranicenja
-- ovde nism ispratio kada ovo prolazi a kada ne, guglaj! (?)
DROP TABLE IF EXISTS bar_unique;
CREATE TABLE bar_unique (UNIQUE (n)) SELECT n FROM foo;

SELECT * FROM bar_unique;


-- pokretanje koda: 
--      mysql -u jovan -p <primer7.sql --auto-vertical-output
