# hocemo da svedemo problem lojdove slagalice na astar algoritam
# prekopirali smo osnovni algoritam iz proslog primera i sada ga samo modifikujemo
# dogovorili smo se da resenje bude da je prazno polje u gornjem levom uglu

from collections import defaultdict
import copy   # modul za duboko kopiranje

# dogovorili smo se da stanje u lojdovoj slagalici reprezentujemo kao nekis string gde je prazno polje oznaceno sa 0
# npr stanje:   2 8 3
#               1 6 4     ->     2:8:3:1:6:4:7:0:5
#               7 _ 5
# ali zgodno nam je i da imamo matricnu reprezentaciju nekog stanja, tako da pisemo dve pomocne funkcije koje ce da rade konverziju izmedju ta dva oblika

# matr -> str
def serialize(state):
    serialized = []
    for row in state:
        for col in row:
            serialized.append(str(col))
    return ':'.join(serialized)


# str -> matr
def deserialize(serialized:str):
    splited = serialized.split(':')
    result = [ 
                splited[:3],
                splited[3:6],
                splited[6:]
             ]
    #ovo je matrica charova sad, a mi hocemo da budu intovi, mogli smo i direktno kad smo pravili matricu
    result = [[int(x) for x in row] for row in result]
    return result


# jedna heristika bi mogla da bude menhetn rastojanje nekog polja do pozicije na kojoj bi trebalo da se nalazi
def h(n):
    deserialized = deserialize(n)
    H = 0
    for i in range(0, 3):
        for j in range(0, 3):
            # vidi se zasto je formula ovde ovakva kada se raspise za neko stanje. Deo sa % racuna u kojoj koloni neki element iz matrice treba da se nalazi (u krajnjem stanju)
            # a deo sa / isto to samo za vrstu
            H += abs(deserialized[i][j] % 3 - j) + abs(deserialized[i][j] / 3 - i)
    return H

# pomocna za heuristiku
def node_in_open_set_with_lowest_heuristic_guess(open_set, heuristic_guess):
    resul = None
    min_path = float('inf')
    for v in open_set:
        hg = heuristic_guess[v]
        if hg < min_path:
            result = v
            min_path = hg
    return result


# pomocna za generisanje mogucih stanja
def get_neighbours(state:str):
    deserialized = deserialize(state)
    neighbours = []
    blank_i = -1
    blank_j = -1
    for i in range(0,3):
        for j in range(0,3):
            if deserialized[i][j] == 0:
                blank_i = i
                blank_j = j
    # ako se prazno polje nalazi u prvom ili drugom redu 
    if blank_i > 0:
        new_matrix = copy.deepcopy(deserialized)  # mora duboko kopiranje zbog nacina kako u pajtonu radi =    (= pravi nov ojekat samo za primitivne tipove, a za sve ostalo dodje kao pokazivac!)
        new_matrix[blank_i][blank_j] = new_matrix[blank_i - 1][blank_j]  # znamo da sigurno ima neki elment iznad
        new_matrix[blank_i - 1][blank_j] = 0
        neighbours.append(serialize(new_matrix))
    # ako se prazno polje nalazi u nultomm ili prvom redu
    if blank_i < 2:
        new_matrix = copy.deepcopy(deserialized)  
        new_matrix[blank_i][blank_j] = new_matrix[blank_i + 1][blank_j]  # znamo da sigurno ima neki elment ispod
        new_matrix[blank_i + 1][blank_j] = 0
        neighbours.append(serialize(new_matrix))
    # ako se prazno polje nalazi u prvoj ili drugo koloni
    if blank_j > 0:
        new_matrix = copy.deepcopy(deserialized)  
        new_matrix[blank_i][blank_j] = new_matrix[blank_i][blank_j - 1]  # znamo da sigurno ima neki elment levo
        new_matrix[blank_i][blank_j - 1] = 0
        neighbours.append(serialize(new_matrix))
    # ako se prazno polje nalazi u nultoj ili prvoj koloni
    if blank_j < 2:
        new_matrix = copy.deepcopy(deserialized)  
        new_matrix[blank_i][blank_j] = new_matrix[blank_i][blank_j + 1]  # znamo da sigurno ima neki elment desno
        new_matrix[blank_i][blank_j + 1] = 0
        neighbours.append(serialize(new_matrix))    

    # tezina grana do svakog susednog stanja je 1 jer se desava samo 1 potez
    return zip(neighbours, [1 for _ in neighbours])        


# u odnosu na osnovni astar algoritam, ne treba na adj_list jer je skroz neprakticno imati vec spremljen skup svih mogucih stanja za lojdovu slagalicu ejr ih ima jako mnogo
# umesto toga implicnitno cemo genereisati stanja kako se kroz njih krecemo. Sve sto nije iskomentarisano je identicno kao u prosloj implementaciji
def astar(start_node, target_node, h):

    # dobijamo pocetno i krajnj stanje kao matricu, a zgodnije nam je da budu stringovi jer ih koristimo kao kljuceve u mapama
    start_node = serialize(start_node)
    target_node = serialize(target_node)

    open_set = set([start_node])

    parents = {}
    parents[start_node] = None
    
    # ova linija je sada nepotrebne
    # cheapest_paths = { v : float('inf') for v in adj_list}
    # umesto njih koristimo defaultdict. Kada pokusamo da pristupimo elementu u dict koji vec postoji, on ce biti vracen, a kada element ne postoji, on ce biti
    # generisan na osnovu funkcije koja se prosledi konstruktoru. Mi ovde hocemo da generisani put bude beskonacno
    cheapest_paths = defaultdict(lambda: float('inf'))
    cheapest_paths[start_node] = 0

    # isto i ovde
    # heuristic_guess = { v : float('inf') for v in adj_list }
    heuristic_guess = defaultdict(lambda: float('inf'))
    heuristic_guess[start_node] = 0

    path_found = False
    iteration = 0       # brojanje iteracija, samo za demonstraciju
    while len(open_set) > 0:
        current_node = node_in_open_set_with_lowest_heuristic_guess(open_set, heuristic_guess)
        if current_node == target_node:
            path_found = True
            break

        open_set.remove(current_node)

        # posto nemamo adj list, pisemo novu funkc koja ce za nas generisati moguca stanja u kojima slagalica moze da se nadje u datom trenutku
        for (neighbour_node, weight) in get_neighbours(current_node):
            new_cheapest_path = cheapest_paths[current_node] + weight
            if new_cheapest_path < cheapest_paths[neighbour_node]:
                parents[neighbour_node] = current_node
                cheapest_paths[neighbour_node] = new_cheapest_path
                heuristic_guess[neighbour_node] = new_cheapest_path + h(neighbour_node)
                if neighbour_node not in open_set:
                    open_set.add(neighbour_node)
        iteration += 1

    path = []
    if path_found:
        while target_node is not None:
           path.append(target_node) 
           target_node = parents[target_node]
        path.reverse()
    
    return (path, iteration)



if __name__ == "__main__":
    start_node = [[2,3,5], [1,4,0], [7,8,6]]    # neko random stanje iz kog pocinjemo
    target_node = [[0,1,2],[3,4,5],[6,7,8]]     # znamo tacno kako treba da izgleda krajnje
    (path, iterations) = astar(start_node, target_node, h)
    print(path)
    print(iterations)
    # primetimo da se broj iteracija razliuje svaki put kada pokrenemo program. Ovo se desava zato sto za otvoren skup cvorova koristimo pajtonov set()
    # a tu nemamo nikakvu garanciju o redosledu podataka u strukturi, tj moze se desiti da drugim redosledom budu razmatrani cvorovi u dva pokretanja
    # jos jedna stvar koja se desava je da u onoj pomocnoj fuknciji node_in_open_set_with_lowest_heuristic_guess zbog te neuredjenosti naidjemo na neki do vise
    
    # na vezbama je poredio ovaj algoritam sa dijkstrinim , mrzi me to da pisem, ispalo je da je astar nasao u oko 200 iteracija a dijkstra u oko 12000
