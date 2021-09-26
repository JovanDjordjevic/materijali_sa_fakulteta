drop database if exists vezbe;
create database vezbe character set = utf8;
use vezbe;

create table person (
    person_id int not null primary key,
    fname varchar(40) not null,
    lname varchar(40) not null,
    created timestamp not null default now() 
);

load xml local infile 'person.xml'
into table person
rows identified by '<person>';

-- **XPath primeri (nastavak)**

-- Funkcija 'LOAD_FILE' nam omogucava da ucitavamo datoteka kao string, sto
-- nam je potrebno za ucitavanje person-dump.xml. Ako pokusavamo LOAD_FILE na bilo kojoj
-- putanji, verovatno cemo dobiti NULL. Putanja mora da bude u 'secure_file-priv' koja
-- moze i da se modifikuje:

-- select @@GLOBAL.secure_file_priv;

-- Komandom 'sudo cp person.xml /var/lib/mysql-file/person.xml' mozemo da premestimo
-- datoteku na odgovarajucu lokaciju i da koristimo LOAD_FILE da ucitavamo
-- U prethodnom primeru smo mogli tako da izbegnemo '--local-infile=1', ali
-- ovde vec mora ovako.

-- Premestimo i 'person-dump.xml' u /var/lib/mysql-file, jer 'person.xml' ima cudan format,
-- pa bi npr. upit '//person/fname' dohvatio samo 'Likame Slar Sungam' tj. troje ljudi
-- umesto sve

-- select LOAD_FILE('/var/lib/mysql-files/person-dump.xml');

set @path = '/var/lib/mysql-files/person-dump.xml';

-- Primer1: Dohvatamo sva imena koja se pojavaljuju u podacima
select ExtractValue(LOAD_FILE(@path), '//field[@name="fname"]');

-- Primer2: Brojimo koliko ljudi se pojavljuje u podacima
select ExtractValue(LOAD_FILE(@path), 'count(//row)');

-- Primer3: Dohvatamo sve informacije o osobi koja ima 'person_id=5'
select ExtractValue(LOAD_FILE(@path), '//field[@name="person_id" and text()=5]/../*');

-- Primer4: Brisemo osobu koja se zove 'Nirtam'
select UpdateXML(LOAD_FILE(@path), '//field[@name="fname" and text()="Nirtam"]/..', '');