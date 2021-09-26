-- Menadzer moze videti plate svojih zaposlenih, 
-- ali ne i zaposlenih ostalih menadzera, kao ni njihove plate. 
-- Napravimo shemu i okidace koji omogucavaju menadzerima 
-- da menjaju plate zaposlenima za koje su zaduzeni

-- Priprema:
create table profiles(
    empid int,              -- id zaposlenog
    name varchar(20),       -- ime
    sqlid varchar(18),      -- neki njegov string id
    mgrid int,              -- id njegovog menadzera
    salary decimal(9,2),    -- plata
    ismgr char(1)           -- da li je menadzer ili ne
);

insert into profiles values
    (0001, 'SuperBoss', 'sboss', NULL, 500000, 'Y'),
    (1001, 'BigBoss', 'gboss', 0001, 200000, 'Y'),
    (1002, 'MySelf', USER, 0001, 250000, 'Y'),
    (2001, 'FirstLine', 'fline', 1001, 100000, 'Y'),
    (2002, 'MiddleMen', 'mmen', 1001, 100000, 'Y'),
    (2003, 'Yeti', 'yeti', 1002, 110000, 'Y'),
    (2004, 'BigFoot', 'bfoot', 1002, 80000, 'N'),
    (3001, 'TinyToon', 'ttoon', 2001, 50000, 'N'),
    (3002, 'Mouse', 'mouse', 2001, 45000, 'N'),
    (3003, 'Whatsisname', 'wname', 2002, 40000, 'N'),
    (3004, 'Hasnoclue', 'hclue', 2002, 38000, 'N'),
    (3005, 'Doesallwork', 'dwork', 2003, 15000, 'N');

select * from profiles;


-- Zadatak1: Mi smo menadzer drugog nivoa:
-- (1002, 'MySelf', USER, 0001, 250000, 'Y')
-- Napraviti pogled koji nam omogucava da vidimo 
-- plate svojih zaposlenih (kao i svoju).
-- Pomoc: Potrebno je koristiti rekurzivni upit.

-- dodamo sebe tabelu, onda sve one koji su ispod nas, onda za svakog od njih
--  rekurzivno sve one koji su ispod njih itd
-- WITH pravi privremenu pomocnu tabelu, to dodje kao neki view
create view my_emps(
    empid, 
    level, 
    salary
) as
with rec(
    empid, 
    level, 
    salary
    ) as (
    -- dodajemo sebe u tabelu
    select P.empid, 0, P.salary
    from profiles as P
    where P.sqlid = USER

    union all
    -- rekurzivno dodajemo ostale (?)
    select P.empid, level-1, P.salary
    from profiles as P, rec as R 
    where R.empid = P.mgrid
        and level > -100        -- ovaj korak nisam skapirao, ovo je kao neka dubina rekurzije (?)
)
select empid, level, salary from rec;

select * from myemps;
-- na osnovu podataka koje smo uneli iznad ispis ovog upita ce biti:
--    empid      level     salary
--    1002           0        250000.00
--    2003           -1       110000.00
--    2004           -1       80000.00
--    3005           -2       15000.00




-- Zadatak2: Napraviti pogled koji nam omogucava
-- da vidimo sledece: 
-- empid, neposredno iz PROFILES
-- name, neposredno iz PROFILES
-- mgrname, ime neposredno nadredjenog
-- salary, plata ako je nas zaposleni, inace NULL
-- sqlid, neposredno iz PROFILES
-- ismgr, neposredno iz PROFILES

create view empis(
    empid, 
    name, 
    mgrname, 
    salary, 
    sqlid, 
    ismgr
) as
select P.empid, P.name, M.name, ME.salary, P.sqlid, P.ismgr
-- podsecanje, left outer join spoji gde moze, ali ostavi sve podatke iz leve
-- tabele,a ako za njih nema odgovarajuci podatak iz desne, onda se dopunjuje sa null
from profiles as P left outer join my_emps as ME on P.empid = ME.empid
    left outer join profiles as M on P.mgrid = M.empid;

select * from emps;



-- Zadatak3: Napraviti okidac koji nam omogucava
-- da dodajemo nove radnike (koji su nam podredjeni)



-- treba da uradimo sledece:
-- 1) zakljucimo ime menadzera naseg nadredjenog na osnovu mgrname 
-- 2) da proverimo da li je taj nadredjeni naseg novog zaposlenog jedan od nasih
--    zaposlenih (tj da je u mgrid u my_emps)
-- 3) da ppreoverimo da li je taj nadredjeni naseg novog zaposlenog menadzer

-- ovo je isto sto i delimiter u mysql, psotavljamo kada u trigeru imamo neke
-- komande koje se zavrsavaju sa ; (?)
-- NOTE: izgleda da ovo nje komentar nego je --# bas deo sintakse (?)
--#SET TERMINATOR @

create trigger emps_insert 
instead of insert on emps
referencing new as n 
for each row mode db2sql
-- ne znam da li je ovo razlika izmedju db2 i mysql ali nismo pre stavljali atomic ovde
begin atomic
    -- ovo je za 1)
    declare mgrid int;          -- ovo je kao neka pomocna promenljiva, u ranijim vezbama smo to radili van trigera i onda referisali sa @ (?)
    declare ismgr char(1);
    set (mgrid, ismgr) = (
        select P.empid, P.ismgr
        from profiles as P
        where n.mgrname = P.name
    )
    -- ovo je za 2) i 3)
    if mgrid not in select(empid from my_emps) or ismgr <> 'Y'
    then
        -- ako nije ispunjen uslov prekidamo izvrsavanje signalom
        signal sqlstate '70000'  set message_text = 'Not authorized!' 
    end if;

    -- ako je sve dobro mozemo da unesemo novog zaposlenog u profiles tabelu
    insert into profiles values 
        (n.empid, n.name, n.sqlid, mgrid, n.salary, n.ismgr);
end@  

--#SET TERMINATOR ;



-- Zadatak4: Napraviti okidac koji nam omogucava
-- da azuriramo informacije o radnicima koji su
-- nam podredjeni


-- Treba da proverimo sledece (za radnika koga menjamo):
-- 1) Da li po starim podacima radnik pripada skupu nasih radnika?
-- 2) Da li po novim podacima radnik pripada skupu nasih radnika?
-- 3) Da li menjamo radnika koji nismo mi?
-- 4) Da li je neko ko ima podredjene dobio vrednost za ismgr = 'N'?
-- 5) Da li je novi nadredjeni naseg radnika menadzer?


--#SET TERMINATOR @

create trigger emps_update 
instead of update on emps
referencing new as n old as o
for each row mode db2sql
begin atomic
    declare new_mgrid int;
    declare old_mgrid int;
    set new_mgrid = (
        select P.empid from profiles as P
        where n.mgrname = P.name
    );
    set old_mgrid = (
        select P.empid from profiles as P 
        where o.mgrname = P.name
    );

    if old_mgrid not in (select empid from my_emps)
        or new_mgrid not in (select empid from my_emps)
        or o.sqlid = USER
        or (0 < (select count(*) from profiles as P
                 where P.mgrid = n.empid)
           and n.empid = 'N')
        or new_mgrid not in (select P.empid from profiles as 
                             where P.ismgr = 'Y')
    then
        signal sqlstate '70000' set message_text = 'Not authorized!';
    end if;

    -- ako je sve u redu unosimo izmene za zaposlenog u profiles tabelu
    update profiles
    set empid = n.empid,
        mgrid = new_mgrid,
        salary = n.salary,
        sqlid = n.sqlid,
        name = n.name,
        ismgr = n.ismgr,
    where empid = o.empid;
end@

--#SET TERMINATOR ;




-- Zadatak5: Napraviti okidac koji nam omogucava
-- da brisemo radnike koji su nam podredjeni (ali ne i samog sebe)
  
-- Treba da proverimo sledece:
-- 1) Da li brisemo nekog naseg zaposlenog?
-- 2) Da li brisemo sebe?
-- 3) Da li taj koga brisemo ima podredjene?

--#SET TERMINATOR @

create trigger emps_delete instead of delete on emps
referencing odl as o 
for each row mode db2sql
begin atomic
    declare mgrid int;
    set mgrid = (select P.empid from profiles as P
                where o.mgrname = P.name
    );
    if o.empid not in (select empid from my_emps)
        or o.sqlid = USER
        or 0 < (select count(*) from profiles as P 
                where P.grid = o.empid)
    then
        signal sqlsate '70000' set message_text = 'Not authorized!';
    end if;

    -- kao je sve u redu mozemo da obrisemo
    delete from profiles where empid = o.empid;
end@

--#SET TERMINATOR ;
  


-- Testiranje

-- INSERT (validan)
insert into emps values
    (4005, 'New Guy', 'Yeti', 35000, 'nguy', 'N');
-- INSERT (nevalidan) (ovde mu je menadzer neko ko nije u nasoj nadleznosti)
insert into emps values
    (4006, 'New Guy1', 'SuperBoss', 12000, 'nguy1', 'N');


-- UPDATE (validan)
update emps
set
    ismgr = 'Y',
    salary = salary * 1.3,
    mgrname = 'MySelf'
where name = 'Doesallwork';
-- UPDATE (nevalidan)
update emps
set
    ismgr = 'Y',
    salary = 1000000,
    mgrname = 'MySelf'
where name = 'MySelf';


-- DELETE (validan)
select * from profiles;
delete from emps
where name = 'BigFoot';
-- DELETE (nevalidan)
delete from emps
where name = 'MySelf';


-- Ciscenje
drop trigger emps_delete;
drop trigger emps_update;
drop trigger emps_insert;
drop view emps;
drop view my_emps;
drop table profiles;
