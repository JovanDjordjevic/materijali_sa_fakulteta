-- demonstracija kako da se prekida triger usled neke neregularnosti

USE vezbe;

-- posto u mysql CHECK ne radi, ovo radimo trigerima koji su PRE unosa
-- jedan nacin da se prekine triger je da npr pozovemo neku funkciju koja ne postoji
-- npr greska() i tu pukne trigger i prekine se, a drugi nacin je pomocu signala
-- da posaljemo poruku koja ce se ispisati


DROP TABLE IF EXISTS test_ocena

CREATE TABLE test_ocena(
    ime VARCHAR(20),
    prezime VARCHAR(20),
    ocena INT
);


-- triger koji ne dozvoljava unos ocene koja niju u opsgu [5,10]
DELIMITER |

CREATE TRIGGER bi_test_ocena
BEFORE INSERT ON test_ocena
FOR EACH ROW 
    BEGIN
        IF NEW.ocena < 5 OR NEW.ocena > 10 THEN
            -- ovako radimo sa signalima, VAZNO: i sqlstate i message_text su rezervisane kljucne
            -- reci i moraju bas tako da se zovu, jedino sto mozemod a menjamo u ovakvom pozivu
            -- je sadrzaj sqlstate-a i poruke
            SIGNAL sqlstate '45000' SET message_text = 'Ocena mora biti u opsegu [5,10]!';
        END IF;
    END;
|

DELIMITER ;


-- unesemo neke vrednosti za proveru
INSERT INTO test_ocena VALUES
    ('Pera', 'Peric', 10)
SELECT * FROM test_ocena;

-- ovo ce da izazove pozivanje signala
INSERT INTO test_ocena VALUES
    ('Mika', 'Mikic', 2)
-- ovaj select se nece ni izvrsiti jer je prekinuto izvrsavanje u trigeru,
-- (naravno ako zakomentarisemo ostatak koda i pokrenemo samo ovaj select
-- videcemo da Mika nije unet u tabelu)
SELECT * FROM test_ocena;


