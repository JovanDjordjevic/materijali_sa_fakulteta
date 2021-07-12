musko(petar).
musko(milos).
musko(janko).
ozenjen(petar).

% u prologu sve promenljive moraju da pocnu sa velikim slovom, konstante i predikati malim slovom
% , je konjukcija   ; je disjunkcija   \+ je negacija
% = se pita da lie unifikabilno  \= se pita da nisu unifikabilni
% == je da su identicko jednaki   \== je da nisu identicki jednaki

% kada hocemo da zapisemo neku formulu, pisemo je nekako "kontra"
% npr: (Ax) (rich(X) & famous(X) => happy(X))
% u prologu se pise:
% happy(X) :- rich(X), famous(X).
% tj to da je X happy zavisi od toga da je rich i famous

% negacije cemo uvek stavljati na kraj izraza, jer ako su na pocetku,a  mi zelimo da izlistamo sva resenja
% desice se neko odsecanje, zbog nacina na koji prolog radi unifikaciju

neozenjen(X) :- musko(X), \+ozenjen(X).
