SELECT  COUNT(*)
FROM    UPISAN_KURS UK JOIN
        PREDMET P ON P.ID_PREDMETA = UK.ID_PREDMETA 
WHERE   P.ID_PREDMETA = ? AND
        P.ID_PREDMETA NOT IN (SELECT ID_PREDMETA FROM STATISTIKA_UPISANIH_KURSEVA) 
WITH    UR