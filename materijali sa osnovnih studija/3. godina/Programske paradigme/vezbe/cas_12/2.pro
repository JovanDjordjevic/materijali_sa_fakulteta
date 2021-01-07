% 4 vrste termova:
/*  atomi,             }atomi i broje vi se nazivaju jos i
    brojevi,             } atomic term
    promenljive,  
    kompozitni termovi
*/

/*atomi:
to su ugl stringovi od lower u upper karaktera, cifara i _, MORAJU da pocnu sa malim slovom 
mogu biti i recenice pod navodnicima :   'Ovo je takodje atom'
*/

/*brojevi:
sve implementacije prologa imaju integer type, a neke imaju i foat
*/

/*promenljive
pocinju VELIKIM slovom ili sa _, ostalo sve isto kao atomi
npr: X, _Y, Primer_promenljive
_   takodje moze biti anionimna promenljiva
*/

/*kompozitni:
saastoje se od:
functor-a (Prolog atoma)
i argumenata (Prolog termovi)
npr is_bigger(horse, X
*/


%Klauze, programi i queriji
/*Klauze su cinjenice i pravila, na osnovu njih definisemo predikate
cinjenice su predikati praceni tackom .
Pravila se sastoje od glave (prediakta) i tela (sekvenca prediakta odvojenih zarezom ,). glava i telo moraju biti razdvojeni sa :-   a na kraju mora tacka .
Programi su sekvence klauza
Queryji su kad mi od prologa trazimo da dokaze neko doredjeno tvrdjenje, on to radi tako sto svim promenljivama pokusa da dodeli neku vrednosti (to se zove Goal Execution), primer:
    mortal(X) :- man(X).
    man(socrates).
    ----
    mortal(socrates)   --ovo je query kokji ce vratiti yes
*/

/*ugradjeni predikati:
oni ne smeju da se koriste kao funktori i tako glava pravila 
npr Equality predikat:   =    mozemo ga pisati i prefiksno kao i svaki drugi ali i infiksno:   =(X,Y) ,  X=Y
npr true i fail
Output predikat:  write('string')  , imamo i predikat za novi red: nl
predikat za ispitaivanje da li je nesto atom:   atom(nesto)
*/

/*matching termova:
termovi su jednaki ako su iste vrednosti ili ako se mogu dodeliti vrednosti promenljivama u termu tako da budu iste neke vrednosti (?)
npr  is_bigger(X,dog) = is_bigger(elephant,dog)    pritisnemo enter i ispise se   X = elephant  yes
npr  p(X,2,2) = p(1,Y,X)   pritisnemo enter i ispise se no, zato sto X prvo bude fiksirano na 1, Y na 2 ali trece X ne moze da bude 2 jer je vec 1
npr p(_,2,2) = p(1,Y,_)    ovo ispise  Y=2 yes, kad koristimo anonimnu tu mzoe biti bilo koja vrednost, ne pazimo kao gore da X ima vec neku vrednos
npr f(a,g(X,Y)) = f(X,Z),   Z= g(W,h(X))    prolazi jer se mogu upariti, bice X=a, Y=h(a), Z=g(a,h(a)), W=a
npr  X = my_functor(Y) prolazi 
*/

