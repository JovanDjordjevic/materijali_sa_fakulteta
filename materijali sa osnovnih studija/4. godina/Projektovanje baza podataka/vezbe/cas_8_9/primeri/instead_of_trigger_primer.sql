-- Pravimo dve tabele za demonstraciju
create table t1(
    c1 int, 
    c2 float
);

insert into t1 values 
(5, 6.0),
(6, 7.0),
(5, 6.0);

create table t2(
    c1 int, 
    c2 float
);
insert into t2 values 
(5, 9.0),
(5, 4.0),
(7, 5.0);

select * from t1;
select * from t2;

-- neki pogled
create view v5(
    c1, 
    c2
) as
select distinct c1, c2
from t1;

select * from v5;

-- recimo da zelimo npr da obrisemo iz ovog pogleda red koji ima c1=5
-- problem je sto u t1 postoji 2 takva reda, a mi u view psoto smo stavili 
-- distint vidimo samo jedan takav. Ako bismo sada pokusali delete, ne bi moglo 
-- jednosznacno da se odredi na koji red iz t1 se ovo odnosi

-- napravicemo instead of delete triger za ovaj pogled
-- NOTE: instead of triger moze da se definise SAMO nad pogledima
-- a ne i nad tabelama
-- old su stari podaci (moglo je iskraceno o) a imamo i new (skraceno n)
-- za nove podatke    (da li ovo uvek mora da se pise (?) )
-- ovo mode db2sql moramo da stavljamo (?)
create trigger v5_delete 
instead of delete on v5
referencing old as old
for each row mode db2sql
    delete from t1 
    where o.c1 = c1 and o.c2 = c2;


-- ali ako sada pokusamo ovaj delete, desice se triger i ovo ce proci
-- zato sto nas isntead of triger ne barata sa v5 podacima 
-- nego bas sa tabelom (naravno u telu instead of trigera moze da bude
-- bilo sta, ne mora delete)
delete from v5
where c1 = 5;


select * from v5;
select * from t1;
select * from t2;

-- ciscenje
drop view v5;
drop table t1;
drop table t2;