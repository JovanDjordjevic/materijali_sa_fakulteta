import cnf as f
from itertools import product
import os

# resavamo problem N dama. na NxN sahovskoj tabli treba da rasporedimo N dama tako da se ne napadaju 
# ideja ovde nam je da zapisemo sva pravila koja moraju da vaze za neki problem u cnf i da pustimo resavac da uradi sve za nas
def n_queens(n):
    cnf = f.CNF()
    # neka nam promenljive budu oblika pij gde je p_i_j tacno ako se na polju (i,j) nalazi dama

    # pravilo: u svakoj koloni nalazi se bar jedna dama(moglo je i analogno za vrste)
    for i in range(n):
        clause = [f'p_{j}_{i}' for j in range(n)] # ovako cemo za neku fiksiranu kolonu i dobiti klauzulu oblika:  p0i | p1i | p2i .... | p(n-1)i
        cnf.add_clause(clause)

    # pravilo: u svakoj vrsti moze da se nadje najvise jedna dama
    # ~(pki & pkj) ovo je pravilo koje zelimo da napisemo, ali posto nam sve treba u cnf, ovde primenimo deMorganovo pravilo
    #              <=> ~pki | ~pkj   i sada je to validna klauzula  (takodje mora da vazi i!=j)
    for k in range(n):
        for i in range(n-1):            # ove su granice za ij da se nebi desavalo da imamo duplo (nesto tipa ~pki | ~pkj   i onda posle  ~pkj | ~pki)
            for j in range(i+1, n):     # nebi bio problem cak ni da smo ostavili da ima ponavljanja, to nece menjati resenje problema ako postoji
                cnf.add_clause( [f'-p_{k}_{i}', f'-p_{k}_{j}'] )
    
    # pravilo: u svakoj koloni moze da se nadje tacno jedna dama
    # slicno, hocemo da kazemo ~(pik & pjk)     <=> ~pik | ~pjk      (takodje mora da vazi i!=j)
    for k in range(n):
        for i in range(n-1):            
            for j in range(i+1, n):
                cnf.add_clause( [f'-p_{i}_{k}', f'-p_{j}_{k}'] )


    # pravilo: nema dama koje se napadaju dijagonalno
    # dva elementa su na istoj dijagonali ako im je apsolutna razlika i vrstama i po kolonama jednaka
    # ~( pij & pkl) gde su (i,j) i (k,l) polja na sitoj dijagonali
    #                  <=> ~pij | ~pkl 
    # da nebi pisali 4 for petlje ugnjezdene, mozemo da iskoristimo funkciju iz itertools za dekartov proizvod (prakticno se svodi na istu stvar)
    for i, j, k, l in product(range(n), range(n), range(n), range(n)):  # moze i kraci zapis product(range(n), repeat=4)
        if k > i and abs(k - i) == abs(l - j):      # k > i da nebi imali ono duplo 
            cnf.add_clause( [f'-p_{i}_{j}', f'-p_{k}_{l}'] )

    # na kraju kada smo zapisali u cnf, pokrenucemo minisat resavac
    minisat_solve(f'{n}_queens', cnf.dimacs(), cnf.number_to_var_name)


def minisat_solve(problem_name, problem_dimacs, number_to_var_name):
    with open(f'{problem_name}.cnf' , 'w') as handle:
        handle.write(problem_dimacs)

    # radim ovo na windowsu i nemam pristup minisat resavacu ovako da mogu da ga pozovem sa system, tako da ovaj program ne radi
    os.system(f'minisat {problem_name}.cnf {problem_name}_result')

    # mozemo da parsiramo ono sto dobijemo iz izlaznog fajla i prikazemo lepo 
    with open(f'{problem_name}_result' , 'r') as result_file:
        lines = result_file.readlines()

        # ako je problem zadovoljiv, u prvom redu u rezultat fajlu ce pisati SAT
        # ako je zadovoljiv, u drugom redu rezultata ce biti jedno resenje
        if(lines[0].startswith('SAT')):
            print("SATISFIABLE")
            var_values = {}
            for var in lines[1].split(' ')[:-1]:        # na kraju reda je 0 i nju mozemo da zanemarimo
                var_number = int(var)
                var_name = number_to_var_name[abs(var_number)]
                var_values[var_name] = var_number > 0
            # hocemo da sortirano prikazemo samo one promenljive koje su True u rezultatu
            true_vars = list(filter(lambda v: v[1], var_values.items()))
            true_vars.sort()
            for var in true_vars:
                print(var)
        else:
            print("UNSATISFIABLE")


if __name__ == '__main__':
    # primer kako zapiseujemo nas cnf pomocu strukture koju smo napravili
    # cnf = f.CNF()
    # cnf.add_clause(['p2', '-p3'])
    # cnf.add_clause(['-p1', 'p2', '-p3'])
    # print(cnf.dimacs())

    n_queens(4)