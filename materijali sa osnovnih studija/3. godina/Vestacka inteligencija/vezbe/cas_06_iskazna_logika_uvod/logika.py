import copy
from itertools import combinations

# na ovom casu radimo neku naivnu implementaciju iskaza, izraza, logike itd u pajtonu, cisto radi demonstracije, kao uvod u ovu oblast
# funkcije koje smo pisali ovde su uglavnom bas velike slozenosti (2^n) i u realnim situacijama nisu upotrebljive. 
# Na kasnijim vezbama cemo videti efikasnije

# pravimo neku klasu koja ce predstavljati formulu.
# Promenljivei konstante su takodje formule. Kombinovanjem formula i operacija and, or, implication, equivalence, negation itd 
# dobijamo opet formule svaka formula ima svoju interpretaciju, tj izracuna se vrednost po nekoj valuaciji

# klasa formula ce biti neka bazna klasa, a sve ostale ce je naslediti i implementirati metode
class Formula:
    def __init__(self):
        self.components = []

    def interpret(self, valuation):
        pass

    # repr nam sluzi da se ne prikazuje ona neka hash vrednost kada se stampa objekat nego neka reprezentacija koju mi kazemo
    # konkretno on je ovo koristio na vezbama da vidi u debugeru lep zapis formula, a ne one hash vrednosti
    def __repr__(self):
        return str(self)

    # u pajtonu mozemo overridovati operatore (guglaj u dokumnetaciji da vidis tacno koje). Kada neka klasa nasledi ovu baznu sa overridovanim operatorima, 
    # i ona ce imati iste te operatore. Ovi pozivi operatora se u pozadini prevode u neke specijalne funkcije. Npr kada pozovemo operator ==, zapravo se u pozadini
    # poziva __eq__(self, rhs) metod(leva strana je self, desna strana je rhs), i slicno za ostale
    def __eq__(self, rhs):                      # self == rhs   =>  self.__eq__(rhs)
        return Eq(self.copy(), rhs.copy())  

    def __and__(self, rhs):                     # self & rhs   =>  self.__and__(rhs)
        return And(self.copy(), rhs.copy())   

    def __or__(self, rhs):                      # self | rhs   =>  self.__or__(rhs)
        return Or(self.copy(), rhs.copy())  

    # dogovor je da za implikaciju koristimo shiftovanje u desno (>>)
    def __rshift__(self, rhs):                  # self >> rhs   =>  self.__rshift__(rhs)
        return Impl(self.copy(), rhs.copy())

    # dogovor je da za implikaciju koristimo -
    def __invert__(self):                       
        return Not(self.copy())

    # posto znamo da je u pajtonu ime samo bind na neki objekat a ne i njegova kopija, definisacemo metod za kopiranje, tj kada pravimo nase fomrule, uvek cemo praviti
    # prave kopije da se slucajno nebi desilo neko neocekivano ponasanje
    def copy(self):
        return copy.deepcopy(self)

    # funkc koja iz nase formule nalazi sve promenljive koje ucestvuju u njoj
    def get_all_variables(self):
        result = set()
        for c in self.components:
            result.update(c.get_all_variables())
        return result

    # ispitujemod a li je formula valjana (tj tautologija), tj da li je tacna u svakoj valuaciji
    def is_valid(self):
        variables = list(self.get_all_variables())    # ova funkc vraca set ali smo je za svaki slucaj castovali u list (ali izgleda da je radilo i bez toga)
        for valuation in all_valuations(variables):
            if self.interpret(valuation) == False:
                return False, valuation      # vracamo da nije valid i prvu valuaciju za koju smo nasli da je u njoj formula netacna
        return True, None

    # formula je zadovoljiva ako postoji neka valuacija u kojoj je tacna
    def is_satisfiable(self):
        variables = list(self.get_all_variables())
        for valuation in all_valuations(variables):
            if self.interpret(valuation) == True:
                return True, valuation
        return False, None

    # kontradikcija je ako ne postoji valuacija u kojoj je tacna
    def is_contradictory(self):
        variables = list(self.get_all_variables())
        for valuation in all_valuations(variables):
            if self.interpret(valuation) == True:
                return False, valuation
        return True, None
    
    # formula je poreciva ako postoji valuacija u kojoj nije tacna
    def is_falsifiable(self):
        variables = list(self.get_all_variables())
        for valuation in all_valuations(variables):
            if self.interpret(valuation) == False:
                return True, valuation
        return False, None

    def all_valuations_that_interpret_to_true(self):
        result = []
        variables = list(self.get_all_variables())
        for valuation in all_valuations(variables):
            if self.interpret(valuation) == True:
                result.append(valuation)
        return result

class Var(Formula):
    def __init__(self, name):
        super().__init__()
        self.name = name
    
    def interpret(self, valuation):
        return valuation[self.name]

    def get_all_variables(self):
        return set([self.name]) 

    def __str__(self):
        return self.name


class Const(Formula):
    def __init__(self, value):
        super().__init__()
        self.value = value

    # za konstantu nam ovo ne treba, tj onanije promenljiva, pa nam odgovara implementacija iz bazne klase gde se vraca prazan skup
    #def get_all_variables(self):
    #    return set([self.name]) 

    def interpret(self, valuation):
        return self.value
    
    def __str__(self):
        return "{}".format( 1 if self.value else 0)


# sve ove operacije and, or... imaju levu i desnu stranu, i izgleda zgodno da mi tu neku inicijalizaiju izdvojimo u nadklasu, ali ispostavice se da to nije zgodno
# zato sto negacija nije binarna operacija, i kasnije kada budemo radili KNF uvek bismo morali da se pitamo da li je operacija binarna ili ne. Resenje koje radimo
# je da cuvamo niz komponenti koji cine leva (lhs) i desna (rhs) strana operacije
class And(Formula):
    def __init__(self, lhs, rhs):
        super().__init__()
        self.components = [lhs, rhs]
    
    def interpret(self, valuation):
        return self.components[0].interpret(valuation) and self.components[1].interpret(valuation)
    
    def __str__(self):
        return f"({self.components[0]}) & ({self.components[1]})"


class Or(Formula):
    def __init__(self, lhs, rhs):
        super().__init__()
        self.components = [lhs, rhs]
    
    def interpret(self, valuation):
        return self.components[0].interpret(valuation) or self.components[1].interpret(valuation)

    def __str__(self):
        return f"({self.components[0]}) | ({self.components[1]})"


class Impl(Formula):
    def __init__(self, lhs, rhs):
        super().__init__()
        self.components = [lhs, rhs]

    # u pajtonu nemamo operator  implikaciju kao sto imamo and ili or, ali mi implikaciju mozemo da zapisemo i na drugi nacin:
    # p => q    <=>    !p ili q
    def interpret(self, valuation):
        return not self.components[0].interpret(valuation) or self.components[1].interpret(valuation)

    def __str__(self):
        # dogovorili smo se da implikaciju pisemo kao >> jer nemamo => operator u pajtonu 
        return f"({self.components[0]}) >> ({self.components[1]})"


class Eq(Formula):
    def __init__(self, lhs, rhs):
        super().__init__()
        self.components = [lhs, rhs]

    def interpret(self, valuation):
        return self.components[0].interpret(valuation) == self.components[1].interpret(valuation)

    def __str__(self):
        # dogovorili smo se da ekvivalenciju pismo kao == posto nemamo operator <=> u pajtonu
        return f"({self.components[0]}) == ({self.components[1]})"


# negacija nema levu i desnu stranu, njen niz komponenti ce imati samo 1 
class Not(Formula):
    def __init__(self, op):
        super().__init__()
        self.components = [op]

    def interpret(self, valuation):
        return not self.components[0].interpret(valuation)

    def __str__(self):
        return f"-({self.components[0]})"    # korisimo - za not


# pomocna funkcija koja ce za date promenljive da generise sve moguce valuacije
# koristimo combinations is itertools
def all_valuations(variables):
    for r in range(len(variables) + 1):
        for true_variables in combinations(variables, r):
            result = {x:False for x in variables}
            result.update({x:True for x in true_variables})
            yield result    # podseti se kako radi yield!


def vars(names):
    # strip() samo skida beline sa leve i desne strane ako postoje
    return [ Var(name.strip()) for name in names.split(',')]

# primeri kako se nase klase koriste i primeri kako resavamo neke probleme sa njima

def primer_1():
    x, y, z = vars("x,y,z")
    #         (x /\ y) \/ (z => y)
    # formula = Or( And(x,y), Impl(z, y) )       # ovako smo pozivali pre nego sto smo overridovali operatore
    formula = (x & y) | (z >> y)
    valuation = { "x" : True,
                  "y" : False,
                  "z" : True
                }
    print(formula)
    print(formula.interpret(valuation))
    print("is valid: ", formula.is_valid())
    print("is satisfiable: ", formula.is_satisfiable())
    print("is falsifiable: ", formula.is_falsifiable())
    print("is contradictory: ", formula.is_contradictory())

def primer_4():
    # u igri mines duimenzija 2x3 dobijena je sledeca konfiguracija:
    # |1|A|C|
    # |1|B|2|
    # A,B,C su neotvorena polja a brojevi oznacavaju broj mina u okolini polja
    # zapisati u iskaznoj logici uslove koji moraju da vaze
    A, B, C = vars("A,B,C")

    # pisemo sve uslove koji moraju da vaze, neki ce se i ponavljati (ali to nam sad nije bitno).
    #  Npr prvi red je sta mora da vazi za jedinicu gore levo. Mina mora biti na polju A ili B
    # i ne sme da se desi da bude i na A i na B, drugi red je za jedinicu dole levo, treci red pa nadalje je za 2 dole levo
    formula = (A | B) & ~(A & B) \
              & (B | A) & ~(B & A) \
              & ~(~A & ~B & ~C) \
              & (A | B) & (B | C) & (A | C) \
              & ~(A & B & C)
    print(formula)
    print("is valid: ", formula.is_valid())
    print("is satisfiable: ", formula.is_satisfiable())
    print("is falsifiable: ", formula.is_falsifiable())
    print("is contradictory: ", formula.is_contradictory())
    print("all valuations: ")
    for val in formula.all_valuations_that_interpret_to_true():
        print(val)

def primer_5():
    # imamo 2 kutije A i B i robot mora da stavi objekat u tacno jednu od njih
    A, B = vars("A,B")
    formula = (A | B) & ~(A & B) & ~(~A & ~B)
    print(formula)
    print("is valid: ", formula.is_valid())
    print("is satisfiable: ", formula.is_satisfiable())
    print("is falsifiable: ", formula.is_falsifiable())
    print("is contradictory: ", formula.is_contradictory())
    print("all valuations: ")
    for val in formula.all_valuations_that_interpret_to_true():
        print(val)

def primer_6():
    # zapisati uslov da se u tabeli 2x2 sa poljima A,B,C,D moze postaviti tacno jedan zeton u svakom redu
    # |A|B|
    # |C|D|
    A, B, C, D = vars("A,B,C,D")
    formula = (A | B) & (C | D) & ~(A & B) & ~(C & D)
    print(formula)
    print("is valid: ", formula.is_valid())
    print("is satisfiable: ", formula.is_satisfiable())
    print("is falsifiable: ", formula.is_falsifiable())
    print("is contradictory: ", formula.is_contradictory())
    print("all valuations: ")
    for val in formula.all_valuations_that_interpret_to_true():
        print(val)

def primer_7():
    # zapisati uslov da bitovi trobitnog polja moraju biti jednaki
    A, B, C= vars("A,B,C")
    formula = (A == B) & (B == C) & (C == A)
    print(formula)
    print("is valid: ", formula.is_valid())
    print("is satisfiable: ", formula.is_satisfiable())
    print("is falsifiable: ", formula.is_falsifiable())
    print("is contradictory: ", formula.is_contradictory())
    print("all valuations: ")
    for val in formula.all_valuations_that_interpret_to_true():
        print(val)

def primer_8():
    # dva dvobitna broja se sabiraju i daju rezultat 3  (moze 1+2, 2+1, 3+0, 0+3)
    # A B
    # C D
    # ----
    # 1 1
    A, B, C, D= vars("A,B,C,D")
    formula = (B | D) & ~(B & D) & (A | C) & ~(A & C)
    print(formula)
    print("is valid: ", formula.is_valid())
    print("is satisfiable: ", formula.is_satisfiable())
    print("is falsifiable: ", formula.is_falsifiable())
    print("is contradictory: ", formula.is_contradictory())
    print("all valuations: ")
    for val in formula.all_valuations_that_interpret_to_true():
        print(val)

def primer_9():
    # zapisati uslov da je 4 bitna reprezentacija broja palindorm ali da bitovi nisu jednaki
    A, B, C, D= vars("A,B,C,D")
    formula = (A == D) & (B == C) & ~(A == B & B == C & C == D)
    print(formula)
    print("is valid: ", formula.is_valid())
    print("is satisfiable: ", formula.is_satisfiable())
    print("is falsifiable: ", formula.is_falsifiable())
    print("is contradictory: ", formula.is_contradictory())
    print("all valuations: ")
    for val in formula.all_valuations_that_interpret_to_true():
        print(val)

def primer_10():
    # tri polja se boje crvenom ili plavom
    # ukoliko jeprvo crveno, druga dva moraju biti iste boje
    # ukoliko je drugo crveno, trece mora biti plavo

    # neka nam je true za crveno, false za plavo
    A, B, C= vars("A,B,C")
    formula = (A >> (B == C)) & (B >> ~C)
    print(formula)
    print("is valid: ", formula.is_valid())
    print("is satisfiable: ", formula.is_satisfiable())
    print("is falsifiable: ", formula.is_falsifiable())
    print("is contradictory: ", formula.is_contradictory())
    print("all valuations: ")
    for val in formula.all_valuations_that_interpret_to_true():
        print(val)

def primer_11():
    '''
        A
       / \\
      B - C
    Temana trougla A,B,C se boje sa dve boje, pri tome ni jedan par temena ne moze imati istu boju.
    '''
    A, B, C = vars("A,B,C")
    formula = ~(A == B) & ~(A == C) & ~(B == C)
    print(formula)
    print("is valid: ", formula.is_valid())
    print("is satisfiable: ", formula.is_satisfiable())
    print("is falsifiable: ", formula.is_falsifiable())
    print("is contradictory: ", formula.is_contradictory())
    print("all valuations: ")
    for val in formula.all_valuations_that_interpret_to_true():
        print(val)
 
def primer_12():
    '''
    |A|B|
    |C|D|
    Tabela 2x2 se boji crvenom ili plavom bojom.
    Ako je polje A ofarbano crvenom onda barem jedno od ostalih polja mora biti plavo.
    Ako je polje D ofarabno plavom onda barem dva ostala moraju biti crvena.
    Ne smeju sva polja biti ofarabana istom bojom.
    '''
    A, B, C, D = vars("A,B,C,D")  # neka true bude crveno, a false plavo
    formula = (A >> (~B | ~C | ~D)) \
            & (~D >> ( (A & B) | (A & C) | (C & B) )) \
            & ~(A == B & B == C & C == D)
    print(formula)
    print("is valid: ", formula.is_valid())
    print("is satisfiable: ", formula.is_satisfiable())
    print("is falsifiable: ", formula.is_falsifiable())
    print("is contradictory: ", formula.is_contradictory())
    print("all valuations: ")
    for val in formula.all_valuations_that_interpret_to_true():
        print(val)

if __name__ == '__main__':
    primer_1()
    print("--------------------------------------")
    primer_4()
    print("--------------------------------------")
    primer_5()
    print("--------------------------------------")
    primer_6()
    print("--------------------------------------")
    primer_7()
    print("--------------------------------------")
    primer_8()
    print("--------------------------------------")
    primer_9()
    print("--------------------------------------")
    primer_10()
    print("--------------------------------------")
    primer_11()
    print("--------------------------------------")
    primer_12()