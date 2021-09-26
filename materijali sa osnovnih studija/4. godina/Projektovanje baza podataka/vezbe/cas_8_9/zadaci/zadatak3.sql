-- Prilikom unosa podataka u tabelu, BEFORE okidaci i uslovi ogranicenja
-- Proveravaju da li su podaci koji se unose ispravi, ali nemaju nacina
-- da ih isprave, vec samo dozvoljavaju ili odbijaju unos

-- Sledeci zadatak demonstrira preusmeravanje losih podataka u drugu tabelu

-- Priprema
create table addresses (
    name varchar(10),
    number int,
    street varchar(30),
    country varchar(10) with default 'CANADA'
);

create table bad_addresses as (
    -- (?)
    select cast(NULL as varchar(30)) as reason, A.*
    from addresses as A
) definition only;  -- kreiranje tabele samo na osnovu definicije bez podataka (?)


-- Zadatak1: Napraviti pogled `adresses_v` identican tabeli addresses

create view addresses_v as
select * from addresses;


-- Zadatak2: Napraviti okidac `insert_addresses_v` koji proverava
-- da li je adresa koja se unosi u tabelu validna
-- Uslovi
-- 1) `number` ne sme da bude NULL
-- 2) `number` mora da bude veci od 0
-- 3) `name` ne sme da bude NULL
-- 4) duzina niske `name` mora da bude veca od 0
-- 5) `street` ne sme da bude NULL
-- 6) duzina niske `street` mora da bude veca od 0
-- 7) `country` ne sme da bude NULL
-- 8) Dozvoljene vrednosti za `country` su:
--    'CANADA', 'USA', 'GERMANY', 'FRANCE', 'SERBIA'
-- Ukoliko uslov nije ispunjen, onda u tabelu `bad_addresses`
-- Uneti odgovarajuci poruku o gresci u okviru kolone `reason`


--#SET TERMINATOR @

create trigger insert_addresses_v instead of insert on adresses_v
referencing new as n
for each row mode db2sql
begin atomic
    -- ovo je razlog koji se unosi u bad_adresses ako adresa ne zadovoljava uslove iz zadatka
    declare reason varchar(30);
    
    set reason = case
        when n.number is null       then 'Number is null'
        when n.number <= 0          then 'Number is not positive'
        when n.name is null         then 'Name is null'
        when length(n.name) = 0     then 'Name is empty'
        when n.street is null       then 'Street is null'
        when length(n.street) = 0   then 'Street is empty'
        when n.country is null      then 'Country is null'
        when n.country not in ('CANADA', 'USA', 'GERMANY', 'FRANCE', 'SERBIA')      
                                    then 'Unknown country'
        else null
    end;

    if reason is not null
    then 
        insert into bad_addresses values 
            (reason, n.name, n.number, n.street, n.country);
    else
        insert into addresses values 
            (n.name, n.number, n.street, n.country);
    end if;
end@

--#SET TERMINATOR ;



-- TESTIRANJE

-- INSERT
insert into addresses_v values
    ('Jones', 510, 'Yonge St.', DEFAULT),
    ('Smith', -1, 'Nowhere', 'USA'),
    (NULL, 38, 'Am Feldweg', 'GERMANY'),
    ('Poubelle', 23, 'Rue De Jardin', 'FRANCE');

select * from addresses;
select * from bad_addresses;


-- Ciscenje
drop trigger insert_addresses_v;
drop view addresses_v;
drop table bad_addresses;
drop table addresses;, 
