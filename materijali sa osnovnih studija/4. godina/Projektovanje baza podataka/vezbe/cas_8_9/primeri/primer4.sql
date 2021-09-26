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


-- pogled kao unija
select view v4 (
    c1,
    c2
) as
    select c1, c2 
    from t1

    union all

    select c1, c2
    from t2;


select * from v4;

-- preko ovakvog pogleda je moguce brisanje zato sto svaki podatak potice iz
-- jedne tabele

-- insert nije moguc zato sto se ne zna tacno u koju bi se tabelu unosilo

-- update jeste moguc
update v4
set c1 = c1 + 1
where c1 = 5;

-- ciscenje
drop view v4;
drop table t1;
drop table t2;