bigger(elephant, horse).
bigger(horse, donkey).
bigger(donkey, dog).

% :- je kao if, a zarez ,  je kao konjukcija
%ove promenljive X,Y    MORAJU!!!!  velikim slovima
%primeti da u drugom is_biggeru imamo   bigger, is_bigger    a ne is_bigger,is_bigger    jer nam je potreban izlaz iz rekurzije

is_bigger(X,Y) :- bigger(X,Y).
is_bigger(X,Y) :- bigger(X,Z), is_bigger(Z,Y).
