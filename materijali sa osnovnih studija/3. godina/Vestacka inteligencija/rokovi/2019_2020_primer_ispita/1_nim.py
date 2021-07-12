import copy

def Min(current_state, alfa=float('-inf'), beta=float('inf')):
    if end(current_state):
        return evaluate(current_state), current_state
    
    best_move = None
    current_best_move_value = float('inf')
    for next_state in get_next_states(current_state):
        opponent_best_move_value, _ = Max(next_state, alfa, beta)
        if opponent_best_move_value < current_best_move_value:
            best_move = next_state
            current_best_move_value = opponent_best_move_value

        if current_best_move_value <= alfa:
            return current_best_move_value, next_state

        if current_best_move_value < beta:
            beta = current_best_move_value

    return current_best_move_value, best_move

def Max(current_state, alfa=float('-inf'), beta=float('inf')):
    if end(current_state):
        return evaluate(current_state), current_state
    
    best_move = None
    current_best_move_value = float('-inf')
    for next_state in get_next_states(current_state):
        opponent_best_move_value, _ = Min(next_state, alfa, beta)
        if opponent_best_move_value > current_best_move_value:
            current_best_move_value = opponent_best_move_value
            best_move = next_state

        if current_best_move_value >= beta:
            return current_best_move_value, next_state
        
        if current_best_move_value > alfa:
            alfa = current_best_move_value

    return current_best_move_value, best_move
# --------------------------------------------------------------------

class Nim:
    def __init__(self):
        self.piles = list([3,4,5])
        self.player_to_move = 'Player'
        self.last_move = None
    
    def play_move(self, move):
        pile = move[0]
        to_remove = move[1]
        self.piles[pile] -= to_remove
        self.last_move = move
        self.player_to_move = 'Computer' if self.player_to_move=='Player' else 'Player'

    def draw_board(self):
        print(" | ".join(map(str, self.piles)))

    def get_winner(self):
        if end(self):
            return 'Computer' if self.player_to_move=='Player' else 'Player'
        return None


def end(state:Nim):
    if state.piles[0] == 0 and state.piles[1] == 0 and state.piles[2] == 0:
        return True
    return False

# NOTE: ovo verovatno nije najbolja evaluacija, protivnik ne radi najbolje poteze koje moze, ali program radi ispravno
def evaluate(state:Nim):
    num_non_zero = 0
    
    if state.piles[0] != 0:
        num_non_zero += 1
    if state.piles[1] != 0:
        num_non_zero += 1
    if state.piles[2] != 0:
        num_non_zero += 1

    evaluation = 0
    if num_non_zero == 1:
        evaluation = -1
    if num_non_zero == 2:
        evaluation = 1

    return evaluation

def get_next_states(state:Nim):
    result = []
    for pile_index in range(0,3):
        for move in range(state.piles[pile_index], 0, -1):
            next_state = copy.deepcopy(state)
            next_state.play_move([pile_index, move])
            result.append(next_state)
    return result



if __name__ == "__main__":
    # neka tabla na pocetku ima 3|4|5 kugica kao na slici
    game = Nim()
    game.draw_board()

    while True:
        # igrac
        print("Next to move: {}".format(game.player_to_move))
        move_input = input().split(',')
        move = [int(move_input[0]), int(move_input[1])]
        game.play_move(move)
        game.draw_board()
        if game.get_winner() == 'Player':
            print('Player won')
            break

        # protivnik
        print("Next to move: {}".format(game.player_to_move))
        _, game_state = Min(game)
        computer_move = game_state.last_move
        game.play_move(computer_move)
        game.draw_board()
        if game.get_winner() == 'Computer':
            print('Computer won')
            break