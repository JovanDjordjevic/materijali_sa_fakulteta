# prekopirali smo kod iz prvog primera i onda smo modifikovali takod a ima alfa beta odsecanje, izmene su oznacene komenatarom
# izmene su samo u min i max funkcijama, sve ostalo je isto

# ideja je da kada min funkcija vidi vrednosti za sva sledeca stanja, on ce odavrati najmanje od njih i sigurno nece
# sledeci put uzeti nesto sto je vece od te vrednosti (tj ne uzima nista vece od BETA)
# maksimizator slicno nece uzimati nista manje od ALFA

# na vezbama je radio poredjenje broja poziva u standardnom minimax i u ovom sa alfa beta odsecanjem, mene je mrzelo
# alfa beta pravi drasticno manje poziva, posebno u prvom potezu (npr standardni u prvom potezu razmatra 59000 slucajeva, dok alfa beta razmatra oko 2300)
# broj odsecanja koje alfa beta radi zavisi od redosleda obilaska mogucih stanja

import copy

# https://www.youtube.com/watch?v=l-hh51ncgDI

# ------------------------------------------------------------------------------------------
# osnovna implementacija:
# imamo 2 funkcije Min i Max koje jedna drugu rekurzivno pozivaju
# njihova uloga je da daju nekakvu procenu na osnovu trenutnog stanja
# potrebno je samo jos da napisemo dodatne funkcije end(), evaluate() i get_next_states() koje zavise od igre koju igramo

# mi zelimo ovde da napravimo simulaciju za iks-oks,  gde racunar vraca optimalni potez kao odgovor na neki nas potez

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
# ------------------------------------------------------------------------------------------


# ------------------------------------------------------------------
class XOState:
    empty = '.'
    def __init__(self):
        self.board = [ [XOState.empty, XOState.empty, XOState.empty],
                       [XOState.empty, XOState.empty, XOState.empty],
                       [XOState.empty, XOState.empty, XOState.empty]
                     ]
        self.curr_player = 'X'
        self.last_move = None
        self.move_count = 0
    
    # potez je oblika [i, j]
    def play_move(self, move):
        i, j = move[0], move[1]
        self.board[i][j] = self.curr_player
        self.curr_player = 'X' if self.curr_player == 'O' else 'O'
        self.last_move = move
        self.move_count += 1

    def draw_board(self):
        print( " | ".join(self.board[0]) )
        print( " | ".join(self.board[1]) )
        print( " | ".join(self.board[2]) )
# ------------------------------------------------------------------

def get_winner(current_state:XOState):
    board = current_state.board

    #proveravamo kolone
    for i in range(0, 3):
        if board[0][i] != XOState.empty and board[0][i] == board[1][i] == board[2][i]:
            return board[0][i]

    #proveravamo redove
    for i in range(0, 3):
        if board[i][0] != XOState.empty and board[i][0] == board[i][1] == board[i][2]:
            return board[i][0]

    #proveravamo dijagonale
    if board[0][0] != XOState.empty and board[0][0] == board[1][1] == board[2][2]:
        return board[0][0]
    if board[0][2] != XOState.empty and board[0][2] == board[1][1] == board[2][0]:
        return board[0][2]

    return None

# pomocna funkcija za min i max algoritam
def end(current_state:XOState):
    winner = get_winner(current_state)
    return winner is not None or current_state.move_count == 9

# pomocna funkcija za min i max algoritam
def evaluate(current_state:XOState):
    winner = get_winner(current_state)  
    result = 0
    if winner == 'X':
        result = 1
    elif winner == 'O':
       result = -1  
    return result

# pomocna funkcija za min i max algoritam
# sledeca stanja generisemo tako sto vidimo gde su rpazna polja i na njih onda odigramo potez tekuceg igraca
def get_next_states(current_state:XOState):
    result = []
    for i in range(0, 3):
        for j in range(0, 3):
            if current_state.board[i][j] == XOState().empty:
                next_state = copy.deepcopy(current_state)
                next_state.play_move([i, j])
                result.append(next_state)
    return result


def read_next_move_from_stdin():   # dogovor je da unosimo potez u obliku:   i,j   i da ga sacuvamo kao [i, j]
    move = input().split(',')
    return [ int(move[0]), int(move[1]) ]

# func ce biti min ili max, zavisi da li ce kompjuter biti X ili O
# X maksimizuje, O minimizuje
def get_next_computer_move(current_state:XOState, func):
    _, state = func(current_state)
    return state.last_move


if __name__ == '__main__':

    game = XOState()
    game.draw_board()

    while True:
        # prvo igra X (korisnik)
        # da smo hteli da kompjuter igra kao X, poziv bi bio next_move = get_next_computer_move(game, Max)
        next_move = read_next_move_from_stdin()     
        game.play_move(next_move)
        game.draw_board()
        if get_winner(game) == 'X':
            print("Player X won")
            break

        # samo posle X-ovog poteza se moze desiti da je nereseno jer on igra prvi a ima ukupno 9 polja  
        if end(game):
            print("Draw")
            break
        
        # igra O, njegove poteze ce igrati racunar
        # O treba da minimizuje (jer mi (tj X) pokusavamo da maksimizujemo)
        next_move = get_next_computer_move(game, Min)
        game.play_move(next_move)
        game.draw_board()
        if get_winner(game) == 'O':
            print("Player O won")
            break