import math

def h(current_pos, end_pos):
    curr_i, curr_j = current_pos
    end_i, end_j = end_pos
    return math.sqrt( abs(end_i-curr_i)**2 + abs(end_j-curr_j)**2 )

def get_pos_with_lowest_heuristic_guess(open_set, heuristic_guess):
    result = None
    min_hg = float('inf')
    for elem in open_set:
        hg = heuristic_guess[elem]
        if hg < min_hg:
            min_hg = hg
            result = elem
    return result

def get_neigbor_states(current_pos):
    curr_i, curr_j = current_pos
    neighbours = []
    for i in range(curr_i-1, curr_i+2):
        for j in range(curr_j-1, curr_j+2):
            if i < 0 or i > 7 or j < 0 or j > 7 or (i == curr_i and j == curr_j) or (njiva[i][j] == 'X') or (njiva[i][j] == '*'):
                continue
            else:
                neighbours.append( ((i,j), 1) )
    return neighbours

def astar(start_pos, end_pos):
    print("DEBUG: ", start_pos, end_pos )
    open_set = set()
    open_set.add(start_pos)

    shortest_path = {}
    shortest_path[start_pos] = 0

    heuristic_guess = {}
    heuristic_guess[start_pos] = 0
    
    parents = {}
    parents[start_pos] = None

    path_found = False
    while len(open_set) > 0:
        current_pos = get_pos_with_lowest_heuristic_guess(open_set, heuristic_guess)
        open_set.remove(current_pos)

        if current_pos == end_pos:
            path_found = True
            break

        for (neighbor, weight) in get_neigbor_states(current_pos):
            if neighbor not in shortest_path:
                shortest_path[neighbor] = float('inf')
                heuristic_guess[neighbor] = float('inf')
                parents[neighbor] = None
            
            possible_shortest_path = shortest_path[current_pos] + weight
            if possible_shortest_path < shortest_path[neighbor]:
                shortest_path[neighbor] = possible_shortest_path
                parents[neighbor] = current_pos
                heuristic_guess[neighbor] = possible_shortest_path + h(neighbor, end_pos)
                if neighbor not in open_set:
                    open_set.add(neighbor)
        
    path = []
    if path_found:
        node = end_pos
        while node is not None:
            path.append(node)
            node = parents[node]
        path.reverse()

    return path


njiva = [ 
            ['-', '-', '-', '-', '-', 'S', '-', '*', ],
            ['-', 'X', 'X', '-', '-', '-', '-', '*', ],
            ['-', '-', 'X', '-', 'X', '-', '*', '-', ],
            ['-', '-', 'X', '-', 'X', '-', '*', '-', ],
            ['X', '-', 'X', '-', '-', '-', '*', '-', ],
            ['-', '-', '-', 'X', '-', '-', '*', '-', ],
            ['-', 'X', 'X', 'X', '-', '-', '*', '-', ],
            ['-', '-', '-', 'P', '-', '-', '*', '-', ]
        ]

start_pos = None
end_pos = None

for i in range(8):
    for j in range(8):
        if njiva[i][j] == 'S':
            end_pos = (i, j)
        if njiva[i][j] == 'P':
            start_pos = (i, j)

path = astar(start_pos, end_pos)

print(path)
# path = [(7, 3), (6, 4), (5, 5), (4, 5), (3, 5), (2, 5), (1, 5), (0, 5)]

for (i,j) in path:
    njiva[i][j] = 'O'

for n in njiva:
    print(n)