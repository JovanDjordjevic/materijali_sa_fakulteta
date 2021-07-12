import json   # biblioteka sa rad sa json fajlovima
from queue import Queue, PriorityQueue 

#NOTE: vidi implementacije ovih algoritama na KiAA

# pravimo pomocnu klasu koja radi kao neki stek, da nebi pisali kabast zapis u iterativnom dfs
# mogli smo kao stek da koristimo i LifoQueue 
class StackElement:
    def __init__(self, node, next_neighbour_index):
        self.node = node
        self.next_neighbour_index = next_neighbour_index
    def __str__(self):
        return f"({self.node}, {self.next_neighbour_index})"    # f"..." je formatiran string

# obilazak u dubinu (iterativno)
def depth_first_traversal_iterative(adj_list, start_node, traversal):
    visited = set()
    # hocemo na steku da imamo neke indekse suseda da bismo znali odakle da pocnemo pretragu kada se vracamo unazad
    # -1 ce nam znaciti da kada se element skine sa steka, obradi se bas on, a ne njegovi susedi (ako pise 5 znaci boradjujemo njegovog petog suseda)
    node_stack = [ StackElement(start_node, -1) ]

    while len(node_stack) > 0:
        current = node_stack[-1]
        neighbours = adj_list[current.node]
        if current.next_neighbour_index == -1:
            current.next_neighbour_index += 1
            traversal.append(current.node)
            visited.add(current.node)
        elif current.next_neighbour_index < len(neighbours):
            unvisited_neighbour_found = False
            while current.next_neighbour_index < len(neighbours):
                (next_node, _) = neighbours[current.next_neighbour_index]
                current.next_neighbour_index += 1
                if next_node not in visited:
                    node_stack.append(StackElement(next_node, -1))
                    unvisited_neighbour_found = True
                    break
            if unvisited_neighbour_found == False:   # ako su svi susedi ovog cvora vec poseceni, skidamo ga sa steka
                node_stack.pop()
        else:
            node_stack.pop()   

    return traversal




# obilazak u dubinu (rekurzivno)
def depth_first_traversal(adj_list, start_node, traversal , visited = set()):
    if start_node in visited:
        return
    visited.add(start_node)
    traversal.append(start_node)

    # nebitna nam je duzina sada pa mozemo da je ignorisemo sa _
    for(next_node, _) in adj_list[start_node]:
        if next_node not in visited:
            # obavezno ovde prosledjujemo visited koji je vec popunjen i ne oslanjamo se na default prazan set
            depth_first_traversal(adj_list, next_node, traversal, visited)


# pretraga u dubinu (rekurzivno)
def depth_first_search(adj_list, start_node, target_node, path, visited = set()):
    # ako je tekuci cvor bas onaj do kog treba da se dodje, znaci da smo nasli put do njega i vracamo put
    path.append(start_node)
    if start_node == target_node:
        return path
    visited.add(start_node)

    # trazimo put preko suseda
    for (next_node, _ ) in adj_list[start_node]:
        if next_node not in visited:
            result = depth_first_search(adj_list, next_node, target_node, path, visited)
            # ako je put nadjen saljemo ga nazad kroz rekurzivne pozive
            if result is not None:
                return result 

    # ako u u gornjoj for petlji nije vec pronadjen put to znaci da preko tekuceg cvora ne posoji put pa treba da ga izbacimo iz path
    path.pop()
    return None


# pretraga u sirinu (iterativno) (ovde hocemo da vrataimo nivoe pretrage)
def breadth_first_traversal(adj_list, start_node):
    visited = set()
    queue = Queue()

    levels = [[]]
    separator_node = None  # hocemo da nam nivoi budu razdvojeni nekim separatorom u queue npr:  grad1 grad2 None grad3 grad4 grad5 None itd
    queue.put(start_node)
    visited.add(start_node)
    queue.put(separator_node)

    while not queue.empty():
        current_node = queue.get()
        if current_node == separator_node:
            if queue.empty():
                break
            queue.put(separator_node)
            levels.append([])
            continue
        levels[-1].append(current_node)
        for (next_node, _) in adj_list[current_node]:
            if next_node not in visited:
                queue.put(next_node)
                visited.add(next_node)
    return levels


# pretraga u sirinu (iterativno)
def breadth_first_search(adj_list, start_node, target_node):
    visited = set()
    queue = Queue()
    queue.put(start_node)
    visited.add(start_node)
    
    # cuvacemo roditelje cvorova koje obradjujemo da bismo na kraju mogli da rekosnstruisemo put
    parents = dict()
    parents[start_node] = None

    path_found = False
    while not queue.empty():
        current_node = queue.get()
        if current_node == target_node:
            path_found = True
            break
        for (next_node, _) in adj_list[current_node]:
            if next_node not in visited:
                queue.put(next_node)
                parents[next_node] = current_node
                visited.add(next_node)
    
    path = []
    if path_found:
        path.append(target_node)
        while True:
            parent_node = parents[target_node]
            if parent_node is None:
                break
            path.append(parent_node)
            target_node = parent_node
        path.reverse()

    return path



def dijkstra(adj_list, start_node, target_node):
    visited = set()
    # pravimo tablu duzina od startnog do svakog ostalog. Ode pravimo mapu pomocu list comprehension
    # kljuc je cvor vrednost je razdaljina (beskonacno do svakog cvora sem od startnog do samog sebe)
    D = {v : float('inf') for v in adj_list}
    D[start_node] = 0

    # u PriorityQueue elementi su u nekom poretku. Mi koristimo cinjenicu da se tuplovi u pajtonu porede po elementima u rastucem poretku
    # dakle ako stavimo da je razdaljina prvi element tupla a cvor drugi, ubacivanjem u PriorityQueue dobicemo da su sortirani po duzinama grane rastuce
    pq = PriorityQueue()
    pq.put( (0, start_node) )

    # za rekonstrukciju puta
    parents = dict()
    parents[start_node] = None

    path_found = False
    while not pq.empty():

        (dist, current_node) = pq.get()

        if current_node == target_node:
            path_found = True
            break
        
        visited.add(current_node)

        for (neighbour, distance_from_current) in adj_list[current_node]:
            if neighbour not in visited:
                old_cost = D[neighbour]
                new_cost = D[current_node] + distance_from_current
                if new_cost < old_cost:
                    pq.put( (new_cost, neighbour))
                    D[neighbour] = new_cost
                    parents[neighbour] = current_node
    
    path = []
    if path_found:
        path.append(target_node)
        while True:
            parent_node = parents[target_node]
            if parent_node is None:
                break
            path.append(parent_node)
            target_node = parent_node
        path.reverse()
    
    return path


# svi nakkraci putevi od nekog cvora do svih ostalih (rekonstrukcija puteva za domaci)
def all_shortest_paths_distances(adj_list, start_node):
    distances = { start_node : 0 }
    queue = Queue()
    queue.put(start_node)

    while not queue.empty():
        current_node = queue.get()
        dist = distances[current_node] # znamo u prvom koraku petlje sigurno postoji bar pocetni cvor u queue
        for (neighbour_node, neighbour_distance) in adj_list[current_node]:
            neighbour_distance += dist
            if neighbour_node not in distances: # ako prvi put u obilasku nailazimo na neki cvor
                queue.put(neighbour_node)
                distances[neighbour_node] = neighbour_distance
            elif neighbour_distance < distances[neighbour_node]: # ako vec ovaj cvor postoji unasoj tabeli, pitamo se da li je novi put kraci
                distances[neighbour_node] = neighbour_distance
    return distances



if __name__ == '__main__':
    with open('cities.json', 'r') as f:
        adj_list = json.load(f)  # ucita json i sam ga je za nas konvertovao u dictionary (ako moze to da uradi)
                                 # dobili smo za svaki grad listu suseda i razdaljine do tih suseda   

        print("--------------------------")
        print("Depth first traversal:")
        traversal = [] # ovde ce biti upisan obilazak
        depth_first_traversal(adj_list, 'Oradea', traversal)
        print(traversal)

        print("--------------------------")
        print("Depth first search:")
        path = []   # bice vracen prvi put na koji se naidje (ali ako vidimo na slici grafa, put koji se nadje nije najkraci)
        depth_first_search(adj_list, 'Drobeta', 'Lugoj', path)
        print(path)

        print("--------------------------")
        print("Breadth first traversal:")
        traversal = breadth_first_traversal(adj_list, 'Drobeta')
        print(traversal)

        print("--------------------------")
        print("Breadth first search:")
        path = breadth_first_search(adj_list, 'Drobeta', 'Lugoj')
        print(path)

        print("--------------------------")
        print("Dijsktra:")
        path = dijkstra(adj_list, 'Drobeta', 'Fagaras')
        print(path)

        print("--------------------------")
        print("All shortest paths:")
        distances = all_shortest_paths_distances(adj_list, 'Drobeta')
        print(distances)

        print("--------------------------")
        print("Depth first traversal iterative:")
        traversal = []
        traversal = depth_first_traversal_iterative(adj_list, 'Oradea', traversal)
        print(traversal)