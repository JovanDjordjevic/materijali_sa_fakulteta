/* 
5. Kreirati SQL iskaz kojim se menja definicija kolone kolicina 
tabele detalji_fakture u smislu promene podešavanja za tip podataka.
*/

USE poslovanje;

-- i modifikaciju mozemo kroz ALTER TABLE pomocu  MODIFY COLUMN
-- NOTE: cela originalna definicija za ovu kolonu je DEVIMAL(8,2) NOT NULL,
-- kada se izvrsi ovaj alter table, psoto nismo naveli not null, znaci da se null
-- vrednosti sada dozvoljavaju. Generalno dobra praksa je da uvek navedemo
-- bukvalno sve sto zelimo detaljno kada menjamo ovako kolone, sve sto ne navedemo
-- dobice svoju neku podrazumevanu vrednost (koja nam mozda ne odgovara)
ALTER TABLE detalji_fakture MODIFY COLUMN kolicina DECIMAL(6, 2);

SHOW CREATE TABLE detalji_fakture;