%   unifikacija i jednakost:
%   atom(X) proverava da li je X atom
%   atomic(X) proverava da li je X atom ili broj
%   number(X) proverava da li je broj, slicno  integer(X), float(X), real(X), 
%   slicno var(X), nonvar(X) itd itd

/*
mozemo da poredimo jednakost i unifikabilnost 
unifikabilnost je zapravo pitanje da li se mogu poklopiti vrednosti X i Y u X=Y

= unifikabilni
\= nisu unifikabilni
== identicno jednaki termovi
\== nisu identino jednaki termovi

*/

uni(X,Y) :- X = Y.
% ovde npr uni(X,Y) vrati yes,  uni(X,5) vrati X=5 yes, uni(4,5) vrati no

jed(X,Y) :- X==Y.
% ovde npr jed(X,Y) vrati no,  jed(X,X)  yes, jed(4,5) vrati no  itd

% aritmeticki operatori
/*
is - aritmeticko izracunavanje
=:=   -da li su aritmeticki jednaki
=\=   -aritmeticki nisu jednaki
<, <=, >, >= 
+,-,*,/,//,div,mod,**     itd
*/

op1(X,Y) :- X is Y.
% ako je X var, njoj se dodeljuje vrednost koja je u Y (koja mora biti poznata)
% u suprotnom ovo se svodi na X =:= Y

%abs(X,AX)
abs(X, X) :- X>=0,   !.
abs(X, AX) :- X<0, AX is -X.
% !. je cut operator, on sluzi za odsecanje pretrage, dakle ako se pogodi da se unifikovalo prvo pravilo onda ne gleda drugo uopste


%rekurzivni predikati
/*sluzi za petlje
*/
musko(mihajlo).
musko(stevan).
musko(petar).
musko(mladen).
musko(rajko).

zensko(milena).
zensko(milica).
zensko(jelena).
zensko(senka).
zensko(mina).
zensko(maja).

roditelj(mihajlo, milica).
roditelj(mihajlo, senka).
roditelj(milena, rajko).
roditelj(maja, petar).
roditelj(maja, mina).
roditelj(stevan, mladen).
roditelj(stevan, jelena).
roditelj(milica, mladen).
roditelj(milica, jelena).

%definisemo rpavilo kada je X majka od Y
majka(X,Y) :- roditelj(X,Y), zensko(X).

otac(X,Y) :- roditelj(X,Y), musko(X).

%Y je brat od X
% potreban nam je uslov X\==Y zato sto bi u suprotnom brat(mladen) vraceno dva puta mladen, da je brat sam sebi
% a cut operator !. nam treba jer bi npr jelenu bio vracen mladen kao brat dva puta jer su za njih data oba roditelja
brat(X,Y) :- musko(Y), roditelj(Z,X) , roditelj(Z,Y), X\==Y,   !.

%Y je ujak od X
ujak(X,Y) :- brat(Z,Y), majka(Z,X).

%rekurzivna pravila:
% Y jre predak od X
predak(X,Y) :- roditelj(Y,X).
predak(X,Y) :- roditelj(Z,X) , predak(Z,Y).

