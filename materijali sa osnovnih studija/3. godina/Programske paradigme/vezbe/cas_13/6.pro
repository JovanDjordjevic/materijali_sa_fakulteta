%constraint programiranje

/* radimo nad konacnim domenom, sastoji se od 3 koraka:
1) generisanje promenljivih i njihovih domena
2) generisanje ogranicenja
3) generisanje resenja 

definisanje domena:
X in D      moze i X :: D     (ako 1 promenljiva uzima vrednosti iz nekog domena D)
Vars in D    ili     Vars :: D    (sve promenljive iz liste Vars uzimaju vrednost iz domena D)

domen definisemo kao interval   [pocetak..korak..kraj]
npr   1..10   je [1,2,3,4,5,6,7,8,9,10]
        1..2..10 je [1,3,5,7,9]
        
postoje neki vec gugradjeni rpedikati za ogranicenja:
Opsta:
    alldifferent(Vars), alldistinct(Vars)
    atmost(N, L, V)     -najvise N elemenata iz liste L jednako termu V
    atleast(N, L, V)
    exactly(N, L ,V)
Aritmeticka:
    !!!!!!!!!!!!!!! OVDE NIJE #<= NEGO #=<, a #>= ostaje tako
    E1 R E2   -E1 i E2 su aritmeticki izrazi a R moze biti nesto od :  #=, #\=, #>=, #=<, #>, #<
    min(L)      -minimalni element iz L, ima i min(E1,E2)
    max(L)          ima i max(E1, E2)
    sum(L)
    
instanciranje (labeliranje) promenljivih:
labeling(Options, Vars)
Options = [] (def)
             = [minimize(E), maximize(E), itd]
             
znaci Options je lista dodatnih opcija
*/

primer(Vars) :- Vars = [X,Y,Z],
                         X :: 1..3,
                         Y :: 2..2..10,
                         Z :: 5..8,
                         Z #> Y,
                         labeling(Vars).
 
% generisanje potpunih kvdrata do 100
primer1(Vars) :- Vars = [X],
                          X :: 1..100,
                          X #= Y*Y,             % primeti da ne moramo da imamo Y u Vars da bi stavili constraint, ovo sto napisali znaci da trazimo X koje je jednako nekom broju Y na kvadrat, solver sam trazi te brojeve za nas
                          labeling(Vars).
      
%primetimo da mozemo i samo primer1 :- ... ako tako uradimo samo ce se ispisati na izlaz (?)   ali tako ispise samo jedno resenje (?) a ako treba da bude vise resenja moramo da stavimo i (Vars) pre :-   (?)    
      
% 9.2   petocifren broj ABCDE sa nekim uslovima           
petocifren :- Vars = [A,B,C,D,E],
                    A :: 1..9,
                    [B, C, D, E] :: 0..9,
                    alldifferent(Vars),
                    labeling( [minimize(A+2*B-3*C+4*D-5*E)], Vars),
                    Broj is 10000*A + 1000*B+100*C+10*D+E,
                    write(Broj), nl.
                    
%9.4 magicni kvdrat, suma 15
magicni(Vars) :- Vars = [X1, X2, X3, X4, X5, X6, X7, X8, X9],
                 Vars :: 1..9,
                 alldifferent(Vars),
                 X1 + X2 + X3 #= 15,
                 X4 + X5 + X6 #= 15,
                 X7 + X8 + X9 #= 15,
                 X1 + X4 + X7 #= 15,
                 X2 + X5 + X8 #= 15,
                 X3 + X6 + X9 #= 15,
                 X1 + X5 + X9 #= 15,
                 X3 + X5 + X7 #= 15,
                 labeling(Vars),
                 write(X1), write(' '),write(X2), write(' '),write(X3), nl,
                 write(X4), write(' '),write(X5), write(' '),write(X6), nl,
                 write(X7), write(' '),write(X8), write(' '),write(X9), nl.
                 
%9.6 TWO + TWO = FOUR
zagonetka(Vars) :- Vars = [T,W,O,F,U,R],
                              Vars :: 0..9,
                              T #\= 0,
                              F #\= 0,
                              alldifferent(Vars),
                              2*(100*T+10*W+O) #= 1000*F+100*O+10*U+R,
                              labeling(Vars),
                              write(' '), write(T),write(W),write(O),nl,
                              write(' +'), write(T),write(W),write(O),nl,
                              write(F), write(O),write(U),write(R),nl,nl, fail.
                              
%pro tip: ako u zadnjoj linij na kraju dodamo        nl, fail.   solver ce namispisati sva resenja bez potrebe za nasim unosom ;
                 
                 
%9.9 pekara sa kiflicama, isti onaj zadatak iz pajtona
pekara(Vars) :- Vars = [H,K],
                        H :: 0..66,
                        K :: 0..100,
                        10*H + 12*K #=< 1200,
                        300*H + 120*K #=< 20000,
                        labeling([maximize(7*H+9*K)], Vars),
                        Zarada is 7*H+9*K,
                        write('max zarada: '),write(Zarada),nl,
                        write('hleba: '),write(H),write(' '),write('kifli: '), write(K). 
                         
    
