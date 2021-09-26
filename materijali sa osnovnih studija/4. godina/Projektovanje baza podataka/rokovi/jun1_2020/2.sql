-- brodovi(ime, vrsta, vlasnik),
-- bitke(ime, datum),
-- ishodi(ime_broda, ime_bitke, rezultat).

--a)
delimiter #

create trigger bi_ishodi
before insert on ishodi 
for each row
    begin
        if new.rezultat not in ('potonuo', 'pobedio') then
            signal sqlstate '45000' set message_text 'nedozvoljen ishod';
        end if;

        if (select count(*) from ishodi where ime_broda == new.ime_broda and rezultat == 'potonuo') == 1 then
            signal sqlstate '45000' set message_text 'potonuli brod ne moze da ucestvuje u novoj bici';
        end if;

        -- ako dodjemo do ovde, insert ce uspeti

    end;
#

delimiter ;


-- b)
delimiter #

create trigger bi_insert_2
before insert on ishodi 
for each row
    begin
        if  
            (
            with pomocna (ime, vlasnik, br) 
            as (select ime, vlasnik, count(*) from brodovi group by vlasnik)
            select p.br 
            from pomocna p join ishodi i on p.ime_broda = i.ime
            ) 
        >= 20 then
            signal sqlstate '45000' set message_text = 'ne sme imati vise od 20 brodova';
        end if;
    end;
#

delimiter ;

-- treba i indentican upit samo da bude before update (?)