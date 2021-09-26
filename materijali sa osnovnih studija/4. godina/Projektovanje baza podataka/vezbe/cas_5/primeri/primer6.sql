-- demonstriranje stranog kljuca

USE vezbe;

-- da bi strani kljucevi imali smisla moramo imati parent i child tabele

-- NOTE: posto u childu imamo strani kljuc, ako prvo pokusamo da obrisemo parent
-- tabelu dobicemo gresku zato sto i dalje postoji neka tabela koja na nju referise
-- dakle prvo moramo da obrisemo child pa tek onda parent
DROP TABLE IF EXISTS child;
DROP TABLE IF EXISTS parent;


CREATE TABLE parent(
    id INT NOT NULL,
    PRIMARY KEY (id)
);


-- dodavanje sranog kljuca mozemo pomocu CONSTRAINT
CREATE TABLE child(
    id INT NOT NULL,
    parent_id INT,
    INDEX par_ind (parent_id),
    CONSTRAINT pk_id PRIMARY KEY (id),  -- jos jedan nacin da dodamo primarni kljuc je da to uradimo pomocu constrainta pri pravljenju tabele
    CONSTRAINT fk_parent_id FOREIGN KEY (parent_id) REFERENCES parent(id)
    ON DELETE CASCADE ON UPDATE CASCADE -- ovako mozemo da navedemo sta se desava kada se nesto iz ove tabele brise/menja
                                        -- ovo se odnosi na ovaj strani kljuc, moglo je i sve u jednom redu
                                        -- DDL bas briga za razmake i nove redove, bitno je samo da stavljamo ; i , na dobra mesta
);

SHOW CREATE TABLE parent;
SHOW CREATE TABLE child;

-- ovako mozemo ubaciti red u tabelu
-- primetimo sledece, ako probamo da izvrsimo sledecu liniju ovde desice se greska
-- hocemo da ubacimo u child podatak gde je id=1 i parent_id=2. Posto u parentu u ovom
-- trenutku ne postoji vrdnost 2, a u childu je naznaceno da je to strani kljuc
-- program ce puci na ovom mestu
--      INSERT INTO child VALUES (1, 2);

-- demosntracija brisanja stranog kljuca
-- kada dropujemo strani kljuc moramo da navedemo kako se zove zato sto tabela moze imati
-- vise stranih kljjuceva (za primarni kljuc nismo morali jer je jedinstven)
ALTER TABLE child DROP FOREIGN KEY fk_parent_id;
SHOW CREATE TABLE child;

-- primetimo da sada ova linija nece pucati zato sto vise ne postoji
-- foreign key constraint
INSERT INTO child VALUES (1, 2);

-- neki jednostavan upit da vidimo unetu vrednost
-- (upiti daju ispis u konzolu slicno kao i SHOW komande koje smo imali do sad)
SELECT * FROM child;

-- pokretanje koda: 
--      mysql -u jovan -p <primer6.sql --auto-vertical-output
