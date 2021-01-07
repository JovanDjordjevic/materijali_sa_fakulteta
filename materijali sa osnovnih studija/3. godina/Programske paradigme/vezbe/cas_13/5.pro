/*liste:
moze biti:  []   prazna lista  i  .(G,R)   gde je G term kji predstavlja glavu a R rep liste   (rep je uvek lista)
primeri:
[]
.(a,[])
.(a,  .(b,[]))
to je kabasto, pa moze ovako:
[a,b,c]  <=>  .(a,  .(b,.(c,[])))
Mozemo to dekomponnovati kao u haskelu, npr mzoe se unifikovati [G|R] = [1,2,3], ne moze se unifikovati [G|R] = []
mozemo to dekomponnovati do proizvoljne dubine npr   [G,  GG|GR] = [1,3,4]   bice G=1, GG=3, GR=[4]
*/

% da li je elem u listi
sadrzi(X, [X|_]) :-  !.    
sadrzi(X, [_|R]) :- sadrzi(X,R).

%moze i ovako:      ; predstavlja logicku disjunkciju
sadrzi1(X, [G|R]) :- G==X ; sadrzi1(X,R).

%vratiti duzinu lsiteu promenljivoj D
duzina([], 0).
duzina([_|R], D) :- duzina(R, D1), D is 1 + D1.

%suma elemenata liste
suma([], 0).
suma( [G|R], S ) :- number(G), suma(R, S1), S is S1 + G.

%aritmeticka sredina
arsr(L,A) :- duzina(L,D), D >0, suma(L,S), A is S/D.

%ucitavanje listu duzine N gde elementi mogu biti proizvoljni termovi, ako N<0 ne ucitavamo
%read ucitava sa standardnog ulaza u promenljivu koju prosledimo
%u prologu . je oznaka z kraj ulaza, znaci kada unesemo neki elment lsite treba da stavmo. iza njega
ucitaj(N, _) :- N<0, !.
ucitaj(0, []).
ucitaj(N, [G|R]) :- N>=1, write('element: '), read(G), nl,  N1 is N-1, ucitaj(N1, R).


%dodavanje na pocetak:
dodajPocetak(X, L, [X|L]).

%dodavanje na kraj
dodajKraj(X, [], [X]).
dodajKraj( X, [G|R], [G| NL] ) :- dodajKraj(X, R , NL).

%brisanje prvog
obrisiPrvi([_|R], R).

%brisanje posldnjeg
obrisiPoslednji([_], []).
obrisiPoslednji( [G|R], [G|R1] ) :- obrisiPoslednji(R,R1).

%deli listu na dve liste u kojoj su pozitivni i ngativni elementi: podeli(L, L1, L2)
podeli([], [], []).
podeli([G|R], [G|R1], L2) :- G>=0, podeli(R, R1, L2).
podeli([G|R], L1, [G|R2]) :- G<0, podeli(R, L1, R2).

%menjamo elemente X sa Y neke liste, zameni(X,Y,L, NL)
zameni( X, Y , [], []).
zameni(X, Y, [X|R],  [Y|R1]) :- zameni(X, Y, R, R1).
zameni(X, Y, [Y|R], [X|R1]) :-  zameni(X, Y, R, R1).
zameni(X, Y, [G|R], [G|R1]) :- G \==X, G\==Y, zameni(X, Y, R, R1).

%sortiranje liste rastuce mergesort
mergeSort([], []).
mergeSort([X], [X]) :- !.
mergeSort(L, NL):- deli(L,A,B), mergeSort(A,NA), mergeSort(B,NB), spoji(NA,NB,NL).

deli([], [], []).
deli([X], [X], []).
deli([G1,G2|R], [G1|R1], [G2|R2]) :- deli(R, R1, R2).

spoji(L, [], L).
spoji([], L, L).
spoji([G1|R1], [G2|R2], [G1|R]) :- G1<G2, spoji(R1, [G2|R2], R).
spoji([G1|R1], [G2|R2], [G2|R]) :- G1>=G2, spoji([G1|R1], R2 , R).
