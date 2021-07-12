# ovde implementiramo neku klasu koja ce nam omoguciti zapis u CNF (?)
# nije pogodno da koristimo onu implementaciju logike sa proslog casa, zato sto se ona razvija u neko kao drvo
# problem sa tim je sto to drvo moze biti veoma duboko i vrlo lako moze da probije stek
# u zvanicnim materijalima Marko je ostavio da primer kako bi radili sa starom implementacijom

class CNF:
    def __init__(self):
        self.clauses = []             # ovo ce izgledati ovako nekako(npr za primer iz notes.txt):   [ ['p2', '-p3'], ['-p1', 'p2', '-p3'] ]
        self.var_name_to_number = {}  # mi cemo zadavati promenljive kao stringove, a za dimacs format za minisat nam trebaju brojevi
        self.number_to_var_name = {}  # da bismo mogli da parsiramo rezultat koji ce minisat vratiti u dimacs formatu

    def add_clause(self, clause):
        for literal in clause:
            var_name = literal.strip('-')  # samo ime promenljive, ignorisemo minus ako ga ima
            # ako prvi put vidimo ovu promenljivu dodajemo je u mape
            if var_name not in self.var_name_to_number:
                var_number = len(self.var_name_to_number) + 1
                self.var_name_to_number[var_name] = var_number
                self.number_to_var_name[var_number] = var_name
        self.clauses.append(clause)
    
    # pravimo reprezentaciju u dimacs formatu
    def dimacs(self):
        result = f'p cnf {len(self.var_name_to_number)} {len(self.clauses)}\n'
        for clause in self.clauses:
            for literal in clause:
                var_name = literal.strip('-')
                if literal[0] == '-':
                    result += '-'
                result += f'{self.var_name_to_number[var_name]} '   # ne zaboravi razmak posle svake promenljive u redu!
            result += '0\n'
        return result
        