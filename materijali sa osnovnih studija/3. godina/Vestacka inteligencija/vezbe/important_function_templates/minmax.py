# potrebne su nam dodatne pomocne funkcije koje zavise od konkretne igre kou simuliramo
#   end(current_state)               - procenjuje da li je krajnje stanje igre
#   evaluate(current_state)          - neka ocena stanja igre
#   get_next_states(current_state)   - moguca naredna stanja u igri

# Obicna minmax implementacija bez alfa-beta odsecanja
def Min(current_state):
    # ako smo u krajnjem stanju ocenjujemo to stanje
    if end(current_state):
        return evaluate(current_state), current_state
    
    #trazimo najbolji potez za nas
    current_best_value = float('inf')    # posto smo u minimizatoru, mi trazimo ono sto je najmanje, pa nam je startna vrednost beskonacno
    best_move = None
    for next_state in get_next_states(current_state):
        # min poziva max i obrnuto
        opponents_best_move_value, _ = Max(next_state)
        if opponents_best_move_value < current_best_value:
            current_best_value = opponents_best_move_value
            best_move = next_state 
    
    return current_best_value, best_move

# analogno minimizatoru
def Max(current_state):
    if end(current_state):
        return evaluate(current_state), current_state

    current_best_value = float('-inf')   # posto smo u maksimizatoru, mi trazimo ono sto je najvece, pa nam je startna vrednost -beskonacno
    for next_state in get_next_states(current_state):
        opponents_best_move_value, _ = Min(next_state)
        if opponents_best_move_value > current_best_value:
            current_best_value = opponents_best_move_value
            best_move = next_state
    
    return current_best_value, best_move

#---------------------------------------------------------------------
# Implementacija sa alfa-beta odsecanjem
def Min(current_state, alpha = float('-inf'), beta = float('inf')):     # IZMENA
    # ako smo u krajnjem stanju ocenjujemo to stanje
    if end(current_state):
        return evaluate(current_state), current_state
    
    #trazimo najbolji potez za nas
    current_best_value = float('inf')    # posto smo u minimizatoru, mi trazimo ono sto je najmanje, pa nam je startna vrednost beskonacno
    best_move = None
    for next_state in get_next_states(current_state):
        # min poziva max i obrnuto
        opponents_best_move_value, _ = Max(next_state, alpha, beta)      # IZMENA
        if opponents_best_move_value < current_best_value:
            current_best_value = opponents_best_move_value
            best_move = next_state 

        # znamo da maksimizator sigurno nece prihvatiti neki potez minimizatora koji je manji od alfa
        # tako da mozemo da odsecemo ovu granu pretrage
        if current_best_value <= alpha:                                         #  NOVO
            #  Umesto next_state moze i da stoji None jer ga necemo ni razmatrati
            return current_best_value, next_state

        if current_best_value < beta:                                           #  NOVO
            beta = current_best_value    
    
    return current_best_value, best_move

# analogno minimizatoru
def Max(current_state, alpha = float('-inf'), beta = float('inf')):      # IZMENA
    if end(current_state):
        return evaluate(current_state), current_state

    current_best_value = float('-inf')   # posto smo u maksimizatoru, mi trazimo ono sto je najvece, pa nam je startna vrednost -beskonacno
    for next_state in get_next_states(current_state):
        opponents_best_move_value, _ = Min(next_state, alpha, beta)      # IZMENA
        if opponents_best_move_value > current_best_value:
            current_best_value = opponents_best_move_value
            best_move = next_state

        # znamo da Min sigurno nece prihvatiti neku vrednost vecu od beta, pa nema poente razmatrati dalje ovu granu
        if current_best_value >= beta:                      #  NOVO
            return current_best_value, next_state

        if current_best_value > alpha:                      #  NOVO
            alpha = current_best_value
    
    return current_best_value, best_move