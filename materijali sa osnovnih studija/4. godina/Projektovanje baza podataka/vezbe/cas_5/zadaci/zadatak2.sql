/* 
2. Neka je kreirana baza podataka poslovanje koja služi za praćenje poslovanja jedne 
firme koja radi sa određenom grupom proizvoda i sarađuje sa određenim brojem drugih firmi. 
Baza podataka poslovanje ima četiri tabele i to: priozvodi, firme, fakture i detalji_fakture.

proizvodi(maticni_broj*, ime, jed_mere)
firme(firma*, naziv_firme, mesto, adresa, telefon)
fakture(sifra_fakture,*, sifra_firme, datum, ulaz_izlaz)
    fakture[sifra_firme] je strani kljuc firme[firma]
detalji_fakture(id*, faktura, red_br, proizvod, kolicina, dan_cena)
    detalji_fakture[faktura] je strani kljuc fakture[sifra_fakture]
    detalji_fakture[proizvod] je strani kljuc proizvodi[maticni_broj]

Pod pretpostavkom da su kreirane baza poslovanje i u njoj tabele proizvodi i firme.
Kreirati tabele fakture i detalji fakture sa zadatim uslovima ogranicenja.
*/

USE poslovanje;

-- pazimo na ovaj redosled brisanja zbog stranog kljuca! 
DROP TABLE IF EXISTS detalji_fakture;
DROP TABLE IF EXISTS fakture;

-- kada je nesto strani kljuc, ono mora biti istog tipa kao u parent tabeli
-- pa ovde pazimo da usaglasimo tip sa onim stio smo pisali u proslom zadatku

-- hocemo da napravimo da sifra_firme vude strani kljuc, ali posto ce se mozda po njemu pretrazivati cesto
-- narpavicemo od njega KEY, sitanksa:   KEY 'ime_kljuca' (od_cega_ga_pravimo)
-- ali dodajemo i foreign key constraint  (KEY dodje isto sto i INDEX (?))
CREATE TABLE fakture(
    sifra_fakture SMALLINT(5) UNSIGNED NOT NULL,
    sifra_firme TINYINT(3) UNSIGNED NOT NULL,
    datum DATE NOT NULL,
    ulaz_izlaz CHAR(1) NOT NULL,
    PRIMARY KEY (sifra_fakture),
    KEY k_sifra_firme (sifra_firme), 
    CONSTRAINT fk_fakture_firme FOREIGN KEY (sifra_firme) REFERENCES firme (firma)
    ON DELETE CASCADE ON UPDATE CASCADE
);


-- vidi AUTO_INCEREMENT u prezentaciji, tldr on uzima prvu slobodnu vrednost kada se tabela popunjava (?)
CREATE TABLE detalji_fakture(
    id MEDIUMINT(8) UNSIGNED NOT NULL AUTO_INCEREMENT,
    faktura SMALLINT(5) UNSIGNED NOT NULL,
    red_br TINYINT(3) UNSIGNED NOT NULL,
    proizvod TINYINT(3) UNSIGNED NOT NULL,
    kolicina DECIMAL(8, 2) NOT NULL,
    dan_cena DECMAL(8, 2) NOT NULL,
    PRIMARY KEY (id),
    KEY k_proizvod (proizvod),
    KEY k_faktura (faktura),
    CONSTRAINT fk_detalji_fakture_proizvodi FOREIGN KEY (proizvodi) REFERENCES proizvodi (maticni_broj)
    ON DELETE CASCADE ON UPDATE CASCADE, -- ovo se odnosi na ovaj strani kljuc, moglo je i sve u jednom redu
                                         -- DDL bas briga za razmake i nove redove, bitno je samo da stavljamo ; i , na dobra mesta
    CONSTRAINT fk_detalji_fakture_fakture FOREIGN KEY (faktura) REFERENCES fakture (sifra_fakture)
    ON DELETE CASCADE ON UPDATE CASCADE                                    
);

SHOW CREATE TABLE fakture;
SHOW CREATE TABLE detalji_fakture;