drop database if exists vezbe;
create database vezbe character set = utf8;
use vezbe;

-- *Ucitavanje xml datoteka u tabelu*
-- U datoteci 'person.xml' se nalazi podaci o listi osoba.
-- Informacije o osobama se zapisuju na razlicite nacin, ali
-- strukture su im iste.
-- Zelimo da ucitamo podatke iz 'person.xml' u mysql tabelu.

-- Neophodno je prvo da napravimo tabelu

create table person (
    person_id int not null primary key,
    fname varchar(40) not null,
    lname varchar(40) not null,
    created timestamp not null default now() 
);

-- Ako se 'created' ne unese, automatski ce se tu postaviti vreme dodavanja reda.

-- Ucitavanje 'person.xml' u tabelu 'person'

-- Napomena:
-- Kada se pokrene mysql server, on se pokrece sa '--secure-file-priv' opcijom,
-- koja nas ogranicava na direktorijume iz kojih mozemo da citamo datoteke.
-- https://stackoverflow.com/questions/32737478/how-should-i-tackle-secure-file-priv-in-mysql

-- Zbog toga dodajemo 'local' ispred 'infile' u sledecem upitu. 
-- Da bismo mogli da koristimo 'local', neophodno je da se ta mogucnost ukljuci preko
-- 'local_infile=1'. Alternativa je da se konektujemo na server sa opcijom '--local-infile=1':
-- 'mysql -u <user> --local-infile=1 -p < <sql-script>'. Vrlo moguce da prva varijanta nece
-- da radi zbog restrikcija. 'LOAD DATA LOCAL INFILE file request rejected due to restrictions on access'
-- https://stackoverflow.com/questions/59993844/error-loading-local-data-is-disabled-this-must-be-enabled-on-both-the-client

SET GLOBAL local_infile=1;

load xml local infile 'person.xml'
into table person
rows identified by '<person>';

-- Ako pri pokretanju skripte, dodamo opciju '--xml', ispis ce biti u xml obliku
-- <row>
--     <field name="person_id">1</field>
--     <field name="fname">Kapek</field>
--     <field name="lname">Sainnouine</field>
--     <field name="created" xsi:nil="true" />
-- </row>

select * from person;

-- Sledecom komandom mozemo da sacuvamo sadrzaj kao xml datoteka:
-- `mysql -u root --xml --local-infile=1 -p < primer1.sql > person-dump.xml`
-- Datoteka 'person-dump.xml' moze da se parsira opet u tabelu.

-- Dokumentacija:
-- https://dev.mysql.com/doc/refman/8.0/en/load-xml.html
-- https://dev.mysql.com/doc/refman/8.0/en/xml-functions.html