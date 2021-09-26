/* 
4. Kreirati SQL iskaz kojim se briše prethodno dodata kolona iz 
zadatka 3.
*/

USE poslovanje;

-- slicno se i brise kolona
ALTER TABLE fakture DROP COLUMN primio;

SHOW CREATE TABLE fakture;