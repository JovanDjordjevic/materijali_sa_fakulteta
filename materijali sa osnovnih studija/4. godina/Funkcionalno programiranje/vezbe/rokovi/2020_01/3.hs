--module Main where

-- Zadatak 3:
-- Potrebno je napraviti model koji ce se koristiti unutar servisa za kupovinu.
-- Svaki korisnik servisa inicijalno ima praznu korpu. Prilikom odabira novog
-- proizvoda, postoji odredjeni period tokom koga se korpa azurira. Nakon
-- azuriranja korpe, ukoliko sve prodje kako treba, korpa je azurirana.
-- Alternativno, moguce je da se dese odredjene greske od kojih se svaka
-- karakerise jednim kodom (Int) pri cemu korpa prestaje da bude validna -
-- samo je bitan kod greske u tom slucaju. Definisati model - tip podataka
-- StanjeKorpe (i nista vise, ne implementirati servis ili operacije) koji
-- tacno definise korpu jednog korisnika.
-- Stanje korpe NE ukljucuje proizvode koje je korisnik servisa ubacio u korpu.

data StanjeKorpe = Empty 
                 | Either Int StanjeKorpe