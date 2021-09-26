/* 
7. Kreirati SQL iskaz kojim se menja definicija kolone dan_cena 
tabele detalji_fakture tako što se naziv kolone iz dan_cena menja 
u cena i pored svega se menjaju podešavanja za tip podataka (u
prvobitnoj definiciji je bilo DECIMAL(8,2)).
*/

USE poslovanje;

-- pomocu MODIFY menjamo samo definiciju, a pomocu CHANGE mozemo da 
-- menjamo i ime i tip i definiciju
-- sintaksa: CHANGE COLUMN 'staro_ime' 'novo_ime' tip
ALTER TABLE detalji_fakture CHANGE COLUMN dan_cena cena DECIMAL(10,2) ;

SHOW CREATE TABLE detalji_fakture;
