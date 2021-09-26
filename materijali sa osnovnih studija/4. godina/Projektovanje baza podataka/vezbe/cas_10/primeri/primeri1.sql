-- za ove primere pretpostavlja se da smo napravili bazu pomocu
-- create.sql skripte
use office;


-- (indeks i kljuc su sinonimi)


/*
1. Primarni kljuc.

Da bi se nad nekim atributom ili grupom atributa napravio primarni 
kljuc, potrebno je da vrednosti koje moze uzeti taj atribut budu 
jedinstvene i da nisu dozvoljene null vrednosti.

Primer: selekcija po tacnoj vrednosti. (u ovom upitu nije postavljen primarni kljuc
to se vidi ako pogledamo u create.sql kako se ova tabela napravila)
*/

-- ova komanda ukljucuje profilisanje upita, tj posle upita dobicemo
-- neke informacije npr koliko se dugo izvrsavao
set profiling = 1;

--Pokretanje upita bez postojanja kljuca nad atributom selekcije.
-- explain analyze ce da nam napise kako se tacno izvrsavao upit,
-- npr za ovaj ispis ce biti nesto tipa:  explain -> filter: ... -> table scan ...
-- tj desio se neki filter po e.id pa scan po e.... Dobijamo i informacije kolika je
-- cena tog upita, koliko redova je procenjeno da je obuhvaceno, vreme itd
-- generalno mi cemo explain analyze da korsitimo da procenimo efikasnost
-- raznih indeksa koje koristimo
explain analyze
select e.id, e.name, e.surname
from Employees as e
where e.id = 500000;

-- ako hocemo da se informacije profilisanja ispisu, koristimo komandu
-- show profiles;   (to je ovde stavljeno na dno celog primera)



 
-- Kreiranje primarnog kljuca nad atributom nad kojim se vrsi 
-- selekcija, e.id. To mozemo da uradimo zato sto je e.id
-- atribut jedinstven i ne dozvoljava null vrednosti. 
alter table Employees add constraint primary key (id);


-- Pokretanje upita sa postojanjem primarnog kljuca da vidimo kako se sad ponasa
explain analyze
select e.id, e.name, e.surname
from Employees as e
where e.id = 500000;


-- Brisanje kljuca.
alter table Employees drop primary key; 


-- Zakljucak je da primarni kljuc znatno ubrzava pretragu.
-- ispis imamo ispod

show profiles;

/*
*************************** 1. row ***************************
EXPLAIN: -> Filter: (e.id = 500000)  (cost=103064.35 rows=99453) (actual time=241.469..462.576 rows=1 loops=1)
    -> Table scan on e  (cost=103064.35 rows=994531) (actual time=0.028..420.555 rows=1000000 loops=1)

*************************** 1. row ***************************
EXPLAIN: -> Rows fetched before execution  (cost=0.00..0.00 rows=1) (actual time=0.000..0.000 rows=1 loops=1)

*************************** 1. row ***************************
Query_ID: 1
Duration: 0.46290475
   Query: explain analyze
select e.id, e.name, e.surname
from Employees as e
where e.id = 500000
*************************** 2. row ***************************
Query_ID: 2
Duration: 5.84539525
   Query: alter table Employees add constraint primary key (id)
*************************** 3. row ***************************
Query_ID: 3
Duration: 0.00021075
   Query: explain analyze
select e.id, e.name, e.surname
from Employees as e
where e.id = 500000
*************************** 4. row ***************************
Query_ID: 4
Duration: 2.95238100
   Query: alter table Employees drop primary key
*/