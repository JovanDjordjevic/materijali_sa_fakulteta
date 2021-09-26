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

-- view sa joinom
create view v3(
    c1, 
    c2, 
    c3
) as
    select t1.c1, t1.c2, t2.c2
    from t1 join t2 on t1.c1 = t2.c1;

select * from v3;


-- za ovako definisan pogled insert nije moguc zato sto se ne zna u koju tabelu
-- bi podatak trebalo da se unese

-- update za ovakav view isto nije moguc jer se ne zna jednoznacno da li 
-- se updatuje u t1 ili t2

-- pomocu delete mozemo da obrisemo samo ako znamo tacno sta
-- nije navedeno na vezbama (?)

-- ciscenje
drop view v3;
drop table t1;
drop table t2;