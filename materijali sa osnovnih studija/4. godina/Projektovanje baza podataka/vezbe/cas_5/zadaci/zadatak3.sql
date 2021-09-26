/* 
3. Kreirati SQL iskaz kojim se dodaje nova kolona sa nazivom 
primio i tipom podataka VARCHAR(50) tabeli fakture.
*/

USE poslovanje;

-- Dodaje se kolona sa ADD COLUMN
-- sitanksa ADD COLUMN 'ime_kolone' tip
ALTER TABLE fakture ADD COLUMN primio VARCHAR(50);

SHOW CREATE TABLE fakture;