/*
2. Obican indeks (koji nije primarni kljuc).

Ubrzava selekciju ako je selekcija velika (tj ako se dobavlja mali broj
torku u odnosu na celu tabelu). Ako je selekcija mala (dobavljamo puno torki),
optimizator moze izabrati da ne koristi indeks uopste, zato sto
bi on potencijalno i usporio izdvajanje. To se desava zatos to na pocetku
obican indeks nije klasterovan (?)

Uglavnom se pretpostavlja da je kod izdvajanja po tacnoj vrednosti 
selekcija veca, dok je kod intervalne selekcije selekcija potencijalno 
manja, ali to ne mora da vazi u opstem slucaju.

Na primer, ukoliko na 1000000 redova imamo ravnomerno rasporedjeno 10 
vrednosti, tada svaku od vrednosti ima oko 100000 redova. Sa druge 
strane, ako imamo uslov jedinstvenosti, onda se po tacnoj vrednosti
izdvaja najvise jedan red. U slucaju intervalnog izdvajanja, takodje
može znatno varirati procenat redova koji su obuhvaceni intervalom.

Primer: izdvajanje po tacnoj vrednosti, primer sa i bez indeksa
   - kada je selekcija velika
   - kada je selekcija mala
*/

use office;
set profiling = 1;


--Primer izdvajanja po tacnoj vrednosti bez kljuca, kada je selekcija velika.
explain analyze
select e.id, e.name, e.surname
from Employees as e
where e.salary = 9000;  -- izdvajamo npr po plati zato sto ona ima moguce
                        -- vrednosti u velikom rasponu (?)


-- Kreiranje indeksa nad atributom izdvajanja.
-- specificno za mysql i innodb masinu, mogu da se koriste samo b stabla
-- cak i ako navedemo hash, ili ne navedemo nista, napravice se b stablo
create index Employees_salary_index on Employees (salary) using btree;


-- Pokretanje upita sa postojanjem indeksa.
explain analyze
select e.id, e.name, e.surname
from Employees as e
where e.salary = 9000;


-- Brisanje indeksa.
drop index Employees_salary_index on Employees;

--Zakljucak: kada je selekcija velika indeks se koristi i ubrzava pretragu.




-- Primer izdvajanja po tacnoj vrednosti kada je selekcija mala.

-- Pokretanje upita bez postojanja indeksa.
explain analyze
select e.id, e.name, e.surname
from Employees as e
where e.years = 2;   -- godine ima manji moguc raspon vrednosti pa koristimo njih (?)


-- Kreiranje indeksa nad atributom izdvajanja.
create index Employees_years_index on Employees (years) using btree;


-- Pokretanje upita sa postojanjem indeksa.
explain analyze
select e.id, e.name, e.surname
from Employees as e
where e.years = 2;


-- Brisanje indeksa.
drop index Employees_years_index on Employees;

/*
Zakljucak: u slucaju da je mala selekcija, optimizator moze izabrati
da ne aktivira indeks. Ako ga i iskoristi, moze se desiti da bude
losije nego da ga ne upitrebi
*/

show profiles;

/*
*************************** 1. row ***************************
EXPLAIN: -> Filter: (e.salary = 9000)  (cost=103143.95 rows=99533) (actual time=103.695..517.141 rows=25 loops=1)
    -> Table scan on e  (cost=103143.95 rows=995327) (actual time=0.064..471.921 rows=1000000 loops=1)

*************************** 1. row ***************************
EXPLAIN: -> Index lookup on e using Employees_salary_index (salary=9000)  (cost=19.37 rows=25) (actual time=0.064..0.257 rows=25 loops=1)

*************************** 1. row ***************************
EXPLAIN: -> Filter: (e.years = 2)  (cost=103143.95 rows=99533) (actual time=0.016..501.551 rows=200066 loops=1)
    -> Table scan on e  (cost=103143.95 rows=995327) (actual time=0.015..452.042 rows=1000000 loops=1)

*************************** 1. row ***************************
EXPLAIN: -> Index lookup on e using Employees_years_index (years=2)  (cost=50266.34 rows=394326) (actual time=0.081..1775.246 rows=200066 loops=1)

*************************** 1. row ***************************
Query_ID: 1
Duration: 0.51749725
   Query: explain analyze
select e.id, e.name, e.surname
from Employees as e
where e.salary = 9000
*************************** 2. row ***************************
Query_ID: 2
Duration: 1.78435350
   Query: create index Employees_salary_index on Employees (salary) using btree
*************************** 3. row ***************************
Query_ID: 3
Duration: 0.00085600
   Query: explain analyze
select e.id, e.name, e.surname
from Employees as e
where e.salary = 9000
*************************** 4. row ***************************
Query_ID: 4
Duration: 0.00958075
   Query: drop index Employees_salary_index on Employees
*************************** 5. row ***************************
Query_ID: 5
Duration: 0.51538525
   Query: explain analyze
select e.id, e.name, e.surname
from Employees as e
where e.years = 2
*************************** 6. row ***************************
Query_ID: 6
Duration: 1.82944375
   Query: create index Employees_years_index on Employees (years) using btree
*************************** 7. row ***************************
Query_ID: 7
Duration: 1.80283500
   Query: explain analyze
select e.id, e.name, e.surname
from Employees as e
where e.years = 2
*************************** 8. row ***************************
Query_ID: 8
Duration: 0.00855075
   Query: drop index Employees_years_index on Employees

*/