import cnf as f
from itertools import product
import os

def sudoku_solve(board):
    n = len(board)
    cnf = f.CNF()

    # neka nam promenljive budu oblika S_i_j_k  tj polje (i,j) sadrzi cifru k
    # kada nam je u tabeli neki broj koji nije 0, to znaci da je taj broj fiksiran. Npr S_0_0_8, a tamo gde su 0 ostavljamo solveru da nadje resenje
    # kada kao klauzulu stavimo samo jendu promenljivu, to solveru mnogo olaksava trazenje jer zna da je ta promenljiva fiksirana i ne mora 
    # da ispituje ostale mogucnosti za nju 
    for row, col in product(range(n), repeat=2):
        number = board[row][col]
        if number != 0:
            cnf.add_clause(f'S_{row}_{col}_{number}')
    
    # pravilo: svako polje mora imati jednu vrednost izmedju 1 i 9
    for row, col in product(range(n), repeat=2):
        # ovaj clause zapravo bude oblika: S_i_j_1  | S_i_j_2 | S_i_j_3 ... S_i_j_9 za svako (i,j)
        clause = [ f'S_{row}_{col}_{number}' for number in range(1, n+1) ]
        cnf.add_clause(clause)

    # pravilo: jedno polje ne sme da sadrzi dva broja (posto je proslo pravilo disjunkcija, moze da se desi da npr na polju i_j bude 5
    # a da takodje na polju i_j bude 1). Ovde moramo to da ogranicimo
    # ~(S_r_c_k & S_r_c_k')  k != k'      =>demorgan     ~S_r_c_k | ~S_r_c_k'
    for row, col in product(range(n), repeat=2):
        for num1, num2 in product(range(1, n+1), repeat=2):
            if num1 < num2:
                clause = [ f'-S_{row}_{col}_{num1}', f'-S_{row}_{col}_{num2}']
                cnf.add_clause(clause)

    # ne sme u istoj koloni da se ponavlja broj
    # ~(S_r_c_k & S_r'_c_k)  r != r-      =>demorgan...
    # ne sme u istom redu da se ponavlja broj
    # ~(S_r_c_k & S_r_c'_k)  c != c-      =>demorgan...
    # ne sme u istom 3x3 podkvadratu da se ponavlja broj
    # ~(S_r_c_k & S_r'_c'_k)  r,c i r'c' u istom kvadratu
    
    #ova tri uslova mozemo u jednom prolazu da pokupimo
    for row1, col1, row2, col2, number in product(range(n), repeat=5):
        number += 1   # posto na range ide od [0,8] za sve pa cak i za number, samo ga uvecamo da broj bude [1,9]
        # primetimo da u uslovu opet stavljamo < a ne != da bi izbegli da duplo dodajemo neku klauzulu gde su promenljive samo u drugom redosledu
        if (col1 == col2 and row1 < row2) \
            or (row1 == row2 and col1 < col2) \
            or ( (row1, col1) != (row2, col2) and same_subsquare(row1, col1, row2, col2, n) ):
            
            cnf.add_clause( [ f'-S_{row1}_{col1}_{number}', f'-S_{row2}_{col2}_{number}'] )

    #pozivamo resavac
    minisat_solve("sudoku", cnf.dimacs(), cnf.number_to_var_name)


def same_subsquare(row1, col1, row2, col2, n):
    # velicina podkvadrata je koren dimenzije table
    block_size = int(n**0.5)
    block_1 = (row1 // block_size, col1 //block_size)
    block_2 = (row2 // block_size, col2 //block_size)
    return block_1 == block_2


# ista funkc iz proslog primera
def minisat_solve(problem_name, problem_dimacs, number_to_var_name):
    with open(f'{problem_name}.cnf' , 'w') as handle:
        handle.write(problem_dimacs)

    # radim ovo na windowsu i nemam pristup minisat resavacu ovako da mogu da ga pozovem sa system, tako da ovaj program ne radi
    os.system(f'minisat {problem_name}.cnf {problem_name}_result')

    with open(f'{problem_name}_result' , 'r') as result_file:
        lines = result_file.readlines()
        if(lines[0].startswith('SAT')):
            print("SATISFIABLE")
            var_values = {}
            for var in lines[1].split(' ')[:-1]: 
                var_number = int(var)
                var_name = number_to_var_name[abs(var_number)]
                var_values[var_name] = var_number > 0
            true_vars = list(filter(lambda v: v[1], var_values.items()))
            true_vars.sort()
            for var in true_vars:
                print(var)
        else:
            print("UNSATISFIABLE")


if __name__ == '__main__':
    board = [
        [8,0,0,0,0,0,0,0,0],
        [0,0,3,6,0,0,0,0,0],
        [0,7,0,0,9,0,2,0,0],
        [0,5,0,0,0,7,0,0,0],
        [0,0,0,0,4,5,7,0,0],
        [0,0,0,1,0,0,0,3,0],
        [0,0,1,0,0,0,0,6,8],
        [0,0,8,5,0,0,0,1,0],
        [0,9,0,0,0,0,4,0,0]
    ]
    sudoku_solve(board)