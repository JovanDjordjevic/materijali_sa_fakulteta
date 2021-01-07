%1. odredjivanje da li je godina prestupna 
%prestupna je ako je deljisa sa 4 i nije deljiva sa 100 ili je deljiva sa 400
prestupna(X) :- X mod 4 =:= 0, X mod 100 =\= 0.
prestupna(X) :- X mod 400 =:= 0.

% 2. odredjivanje koliko dana ima prosledjeni mesec
% brdana(mesec, godina, pronmenljiva_u_koju_upisemo_rezultat)
brdana(januar, _, 31 ).
brdana(mart, _, 31 ).
brdana(maj, _, 31 ).
brdana(jul, _, 31 ).
brdana(avgust, _, 31 ).
brdana(oktobar, _, 31 ).
brdana(decembar, _, 31 ).
brdana(april, _,30).
brdana(jun, _,30).
brdana(septembar, _,30).
brdana(novembar, _,30).
brdana(februar, X, 28) :- not(prestupna(X)).
brdana(februar, X, 29) :- prestupna(X).

%3. odrediti max dva broja i smestiti u promenljivu M
maksimum(A, B, M) :- A>=B, M is A.
maksimum(A, B, M) :- A<B, M is B.

% mogli smo i bez promenljive M:
maksimum1(A, B, A) :- A>=B.
maksimum1(A, B, B) :- A<B.
% a moze i jos krace
maksimum2(A, B, A) :- A>=B, !.
maksimum2(_, B, B) .


%4. suma prvih n brojeva upisuje u promenljivu S
%ne mozemo u rekurziji kao u sotalim jezicima da stavimo suma(N-1, S1) zato sto nam nece proci uparivanje, kada se pozove funkcija N, to N je fiksirano, i kada pokusa da matchuje N i N-1 vratice netacno, ali ako uvedemo dodatnu promenljivu onda moze
suma(1,1).
suma(N,S) :- N>1, N1 is N-1, suma(N1,  S1), S is S1 + N.

%5.suma parnih od 2 do N
sumaParnih(2,2).
sumaParnih(N,S) :- N>2, N1 is N-2, sumaParnih(N1,S1), S is S1+N.

%6. proizvod prvih N prirodnih
proizvod(1,1).
proizvod(N,P) :- N>1, N1 is N-1, proizvod(N1, P1), P is P1*N.

%8.
cifra(0,nula).
cifra(1,jedan).
cifra(2,dva).
cifra(3,tri).
cifra(4,cetiri).
cifra(5,pet).
cifra(6,sest).
cifra(7,sedam).
cifra(8,osam).
cifra(9,devet).

cifre(N) :- N<0, !.         %ako je N manje od jedan prekini izvrsavanje, ne trazi dalje
cifre(N) :- N>=0, N<10, cifra(N,R), write(R), nl, !.
cifre(N) :- N>=10, N1 is (N//10), cifre(N1), N2 is (N mod 10), cifre(N2).



