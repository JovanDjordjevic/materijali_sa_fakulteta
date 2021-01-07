rafinerija :- Vars = [B, D],
                   B :: 150000..300000,
                   D :: 300000..325000,
                   D #>= 2 * B,
                   B+D #=< 600000,
                   labeling( [maximize(2*B + 1*D)], Vars),
                   Zarada = 2*B + 1*D,
                   write('zarada : '), write(Zarada),nl,
                   write('benzina : '), write(B),nl,
                   write('dziela : '), write(D),nl.
                   
