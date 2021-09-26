drop database if exists vezbe;
create database vezbe character set = utf8;
use vezbe;

-- *Ucitavanje xml datoteka u tabelu drugacijeg formata*
-- Opet zelimo da ucitamo xml datoteku u tabelu, ali ovog puta
-- se ne poklapaju format tabele i xml datoteke

create table person (
    individual_id int not null primary key,
    name1 varchar(40) not null,
    name2 varchar(40) not null,
    made timestamp not null default now() 
);

load xml local infile 'person-dump.xml'
into table person;

select * from person;

-- Prethodnim upitom smo dobili neispravne podatke, je sistem nije uspeo
-- da pronadje odgovarajuce elemente (sa odgovarajucom strukturom)
-- Moramo da eksplicitno navedemo koji atribut odgovara kom polju elementa '<person>'

-- Brisanje djubreta
delete from person;

load xml local infile 'person-dump.xml'
into table person (@person_id, @fname, @lname, @created)
set individual_id=@person_id, name1=@fname, name2=@lname, made=@created;

select * from person;

-- Sada je unos ispravan
