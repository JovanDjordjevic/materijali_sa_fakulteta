-- demonstracija nekih trigera

-- pretpostavimo da mozemo da korsitimo bazu 'vezbe' od ranije
USE vezbe;

DROP TABLE IF EXISTS account;
CREATE TABLE account(
    acct_num INT,
    amount DECIMAL(10, 2)
);

-- kreiramo triger kojim se sabiraju iznosi koji se unose u tabelu
-- nisam bas lepo ispratio sve (?)
-- sa NEW. pristupamo vrednosti koja se unosi
-- ako izvrsavamo vise od jedne komande za svaki red, moramo da ogradimos ve sa
-- BEGIN i END(?)
CREATE TRIGGER ins_sum 
BEORE INSERT ON account
FOR EACH ROW                            -- kazemo da se telo trigera izvrsava pre svakog ubacivanja nekog reda u tabelu
    SET @sum = @sum + NEW.samount;      -- promenljive sa @ su neke kao pomocne globalne promenljive (?), sa NEW mozemo da dohvatimo vrednosti
                                        -- koje treba da se ubace u tabelu u trenutku kada se triger pozove

-- inicijalizujemo pomocnu promenljivu sum
SET @sum = 0

-- unosimo vrednosti (pre ovoga ce se desiti triger)
-- psoto unosimo 3 reda, a stavili smo FOR EACH ROW, @sum ce se povecati 3 puta
INSERT INTO account VALUES
    (100, 15.00),
    (101, 25.30),
    (105, -100.50);

-- ispisemo sumu koju smo racunali trigerom
SELECT @sum AS 'Total amount inserted';



-- NOTE: kada napravimo triger, on ima uticaja na buduce inserte, ne moze da radi unatrag
-- znaci ovaj triger iz linije 42 nece biti pozvan na insert iz linije 28!
-- kreiramo triger koji sabira prilive i odlive
-- zelimo da se ovo desi pre ins_sum trigera pa koritimo PRECEEDS!
CREATE TRIGGER ins_transaction
BEFORE INSERT ON account
FOR EACH ROW PRECEEDS ins_sum   -- obrati paznju da se PRECEEDS stavlja ovde!! 
    SET @deposits = @deposits + IF(NEW.amount < 0, NEW.amout, 0),
        @withdrawals = @withdrawals + IF(NEW.amount < 0, -NEW.amout, 0)

SET @deposits = 0;
SET @withdrawals = 0;

INSERT INTO account VALUES
    (100, 30.00),
    (101, 40.30),
    (105, -120.50);


SELECT @deposits AS 'Deposits', @withdrawals AS 'Withdrawals';


-- ovde pravimo trigger kjim se amount postavlja da bude u opsegu [0,100]
-- ovde imamo jos par stvari: kada imamo vise komandi motamo da koristimo BEGIN i END
-- vidimo i kako se koristi IF
-- potrebno nam je da imamo i delimiter za komande i za sam trigger
-- nisam abs ispratio zasto je potrebno da uvedemo // kao novi delimiter umesto da samo
-- i dalje imamo ; (to se izgleda radi kada sam trigger ima vise instrukcija)
DELIMITER //

CREATE TRIGGER ins_check
BEFORE INSERT ON account
FOR EACH ROW
    BEGIN
        IF NEW.amount < 0 THEN
            SET NEW.amount = 0;
        ELSEIF NEW.amount > 100 THEN
            SET NEW.amount = 100;
        END IF;
    END;
//

-- ovde vracamo delimiter na staro
DELIMITER ;

INSERT INTO account VALUES
    (200, 30.00),
    (201, 140.30),
    (205, -120.50);

SELECT * FROM account;