-- Date su tabele PERSONS, EMPLOYEES i STUDENTS

create table persons(
    ssn int not null primary key,
    name varchar(20) not null
);

create table employees(
    ssn int not null primary key,
    company varchar(20) not null,
    salary decimal(9, 2),
    foreign key (ssn) references persons(ssn)
    -- on update restrict znaci da ne dozvoljavamo da se desi update (?)
    on delete cascade on update restrict
);

create table students(
    ssn int not null primary key,
    university varchar(20) not null,
    major varchar(20),
    foreign key (ssn) references persons(ssn)
    on delete cascade on update restrict
);


-- Zadatak1: Napraviti pogled `info` koji spaja ove podatke u jedno
-- Motivacija: Spajanje ovih tabela u jedno moze biti zahtevno, 
-- tako da pravimo pogled

-- Svaka osoba se nalazi u tabeli 'persons'. Mozemo da dodamo
-- informacije o poslu i o studiranju preko 'left join'.
-- To znaci da ako osoba nije student, ona ce za te kolone imati
-- nedostajuce vrednosti. Takodje, ako osoba nije zaposlena
-- ona ce za odgovarajuce kolone imati nedeostajuce vrednosti.

create view infor as 
select P.ssn, P.name, E.company, E.salary, S.university, S.major
from persons as P left outer join employees as E 
    on P.ssn = E.ssn
left outer join students as S 
    on P.ssn = S.ssn





-- Zadatak2: Ne mozemo brisati iz prethodno definisanog pogleda
-- Napraviti okidac `info_delete` koji omogucava brisanje iz pogleda
-- preko kolone `ssn`


-- dovoljno je da brisemo iz persons jer je podeseno kaskadno brisanje

--#SET TERMINATOR @

create trigger info_delete instead of delete on info
referencing old as o 
for each row mode db2sql
begin atomic
    delete from persons where ssn = o.ssn;
end@

--#SET TERMINATOR ;




-- Zadatak3: Ne mozemo da dodajemo nove redove 
-- u prethodno definisanom pogledu
-- Napraviti okidac `info insert` koji omogucava dodavanje redova u pogled,
-- a samim tim i indirektno dodavanje u tabele


-- moramo prvo da dodamo u tabelu persons. Ako osoba vec postoji, cela 
-- atomic operacija ce da bude neuspesna
-- ako osoba ima posao treba da bude unesena u employees, a ako ima
-- informaciju o unievrzitetu onda unosimo u student

--#SET TERMINATOR @

create trigger info_insert instead of insert on info
referencing new as n 
for each row mode db2sql
begin atomic
    insert into persons values  -- ako osoba vec postoji, ovde ce da pukne
        (n.ssn, n.name);
    if n.company is not null
    then 
        insert into employees values
            (n.ssn, n.company, n.salary);
    end if;
    if  n.university is not null
    then 
        insert into students values
            (n.ssn, n.university, n.major);
    end if;
end@

--#SET TERMINATOR ;




-- Zadatak4: Ne mozemo da menjamo vrednosti redova
-- u prethodno definisanom pogledu
-- Napraviti okidac `info update` koji omogucava azuriranje redova u pogled,
-- a smim tim i indirektno azuriranje u tabelama


-- Ako se menja kolona 'ssn' u tabeli 'persons', onda se narusava integritet stranog kljuca.
-- Mozemo da dodamo novi ssn u tabelu 'persons', a izmenimo ostale tabele i da obrisemo stari ssn.
-- Ako osoba nije bila student a sada jeste, potrebno je da se izvrsi dodavanje u tabelu 'students'.
-- Ako je osoba bila student, a sada nije, potrebno je izvrsiti  brisanje iz tabele 'student'.
-- Ako je osoba bila student, ali je promenila fakultet ili smer, onda je potrebno izvrsiti azuriranje tabele 'student'.
-- Inace, ako osoba nije bila student, niti postaje student, nije potrebno vrsiti bi koju operaciju.


--#SET TERMINATOR @

create trigger info_update instead of update on info
referencing old as o new as n
for each row mode db2sql
begin atomic
    if o.ssn <> n.ssn
    then
        insert into persons values (n.ssn, n.name);
    end if;

    if o.university is null
    then 
        if n.university is not null
        then
            insert into students values (n.ssn, n.university, n.major);
        end if;
    else    -- ako je osoba bila student pre a sada nije
        if n.university is null
        then
            delete from students 
            where ssn = n.ssn;
        else -- bila stud / promenila faks
            update students 
            set ssn = n.ssn,
                university = n.university,
                major = n.major
            where ssn = o.ssn;
        end if;
    end if;
    
    -- za posao sve analogno
    if o.company is null
    then
        if n.company is not null
        then
            insert into employees values (n.ssn, n.company, n.salary);
        end if;
    else 
        if n.company is null
        then delete from employees
             where ssn = n.ssn;
        else
            update employees 
            set ssn = n.ssn,
                company = n.company,
                salary = n.salary
            where ssn = o.ssn;
        end if;
    end if;

    -- brisemo stari ssn osobe ako je dodat novi
    -- kaksadno ce biti obrisani potrebni podaci iz ostalih tabela
    if o.ssn <> n.ssn
    then 
        delete from persons
        where ssn = o.ssn;
    end if;
end@

--#SET TERMINATOR ;



-- Testiranje

-- INSERT 
insert into info values
    (123456, 'Smith', NULL, NULL, NULL, NULL),
    (234567, 'Jones', 'Wmart', 20000, NULL, NULL),
    (345678, 'Miller', NULL, NULL, 'Harvard', 'Math'),
    (456789, 'McNuts', 'SelfEmp', 60000, 'UCLA', 'CS');
select * from info;
select * from persons;
select * from employees;
select * from students;

-- DELETE
delete from info
    where ssn = 456789;

select * from info;
select * from persons;
select * from employees;
select * from students;

-- UPDATE
update info
set
    ssn = 654321,
    name = 'Marko',
    company = 'SamSvojGazda',
    salary = 100000,
    university = 'MATF',
    major = 'I'
where ssn = 234567;

select * from info;
select * from persons;
select * from employees;
select * from students;

-- Ciscenje
drop trigger info_update;
drop trigger info_insert;
drop trigger info_delete;
drop view info;
drop table students;
drop table employees;
drop table persons;
