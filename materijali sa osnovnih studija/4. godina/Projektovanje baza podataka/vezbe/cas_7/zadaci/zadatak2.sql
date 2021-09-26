/*
2. Sastaviti SQL skript koji kao rezultat daje šifre i imena 
fudbalera, ali samo za one fudbalere koji su dali bar dva 
gola i to na nekoj od utakmica na kojoj je njihov tim pobedio, 
i pritom su tačno dva gola tog fudbalera bili ujedno i 
poslednji golovi na utakmici.
*/

USE FudbalskiSavez;


CREATE OR REPLACE VIEW Uslov(
    SifF,
    SifU
) AS
    SELECT F.SifF, U.SifU
    FROM FUDBALER F, UTAKMICA U, GOL G
    WHERE F.SifF = G.SifF
        AND G.SifU = U.SifU
        AND ( (F.SifT = U.SifTDomaci AND Ishod = '1') 
              OR
              (F.SifT = U.SifTGost AND Ishod = '2')
            )
        AND NOT EXISTS (SELECT SifF
                        FROM GOL L
                        -- podsecanje, <> je za nejednakost
                        WHERE L.SifF <> F.SifF
                        AND L.SifU = U.SifU
                        AND L.Minut > G.Minut)
    GROUP BY F.SifF, U.SifU
    HAVING  COUNT(*) = 2;


SELECT DISTINCT F.SifF, F.Ime 
FROM FUSBALER F. Uslov U 
WHERE F.SifF = U.SifF

-- unos podataka i provera za domaci