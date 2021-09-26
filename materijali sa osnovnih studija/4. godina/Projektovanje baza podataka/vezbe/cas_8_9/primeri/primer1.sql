-- Upustvo za pokretanje db2:
-- * pokretanje db2: db2start 
-- * povezivanje na mstud bazu: db2 connect to mstud;
-- 
-- Prevodjenje skriptova:
-- * db2 < name.sql
--
-- Opcije:
-- * -t ~ postaviti da ';' razdvaja upite.
-- * -f ~ cita upit iz datoteke, cije je ime naredni arg
-- * -v ~ 'echo' upita
-- 
-- Zadatke na vebama pokrecemo ovako:
-- * db2 -tvf name.sql > out.txt


-- Pravimo dve tabele za demonstraciju
create table t1(c1 int, c2 float);
insert into t1 values 
(5, 6.0),
(6, 7.0),
(5, 6.0);

create table t2(c1 int, c2 float);
insert into t2 values 
(5, 9.0),
(5, 4.0),
(7, 5.0);

select * from t1;
select * from t2;

-- pravimo neki pogled
create view v1(
    c1
) as
    select c1 
    from t1
    where c2 > 0;

select * from v1;


-- pogledi se obicno koriste za razdvajanje logicke seme od fizicke i to za posledicu
-- ima nemogucnost izvrsavanja delete i insert operacija osim u nekim jednostavnim 
-- slucajevima, npr kad je neka nedvosmislena akcija 
-- kada ne znamo sta tacno treba da radimo, ili kad nemamo pristup podacima
-- koje zelimo da izmenimo, koristicemo  instead of  okidace
-- oni se aktiviraju kada pokusamo insert/delete/update nad nekim pogledom
-- i onda se UMESTO insert/delete/update izvrsi ono sto je u trigeru

insert into v1 (c1) values
    (1), (2), (3), (4), (5);

-- mi pomocu v1 mozemo dodati samo vrednosti za kolonu c1, pritom ce ostali
-- atributi koje ne mozemo direktno da postavimo biti postavljeni na svoju
-- podrazumevanu vrenodst 0, null...
-- pogled ce nam u selectu dati isti rezultat iako je tabela izmenjena, jer c2
-- za nove podatke ima verdnost 0 a po njoj se gleda sta ide u view
select * from v1;
select * from t1;


-- brisanje moze da se radi samo po  vidljivim podacima
delete from v1 
where c1 = 6

select * from v1;
select * from t1;


-- azuriranje  isto moze samo po vildjivim kolonama
update v1
set c1 = c1 + 5
where c1 = 5;

drop view v1;
drop table t1;
drop table t2;