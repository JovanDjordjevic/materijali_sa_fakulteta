
# za ovaj algoritam potrebne su nam neke dodatne funkcije:
#   h(element) - vraca heuristicku procenu za element (zavisi od problema)
#   node_in_open_set_with_lowest_heuristic_guess(open_set, heuristic_guess)    - za biranje sledeceg cvora koji posecujemo (primer ispod) (naravno moze se integrisati i u samu astar funkciju)

def astar(adj_list, start_node, target_node, h):
    # ovo ce biti skup iz kog cemo u svakom koraku birati neki cvor
    open_set = set([start_node])

    # za rekonstrukciju puteva
    parents = {}
    parents[start_node] = None

    # na pocetku su sve duzine puteva beskonacno
    cheapest_paths = { v : float('inf') for v in adj_list}
    cheapest_paths[start_node] = 0

    # pored do sada nadjene razdaljine, u astar nam je za svaki cvor potrebna jos i informacija sta nam heuristika kaze za duzinu puta do tog cvora
    heuristic_guess = { v : float('inf') for v in adj_list }
    heuristic_guess[start_node] = 0

    path_found = False
    while len(open_set) > 0:
        # iz otvorenog skupa cvorova biramo onaj za koji heuristika kaze da je najbolji
        # kod dijsktre smo u ovom koraku uzimali najblizi cvor iz queue (dakle po razdaljini koju do sada znamo, a ne heuristici)
        # ovaj korak ne znaci da mi ignorisemo vec postojece najkrace puteve. U nekoj liniji ispod vidi se kako se azurira heuristika, 
        # tj vidi se da svakako najkraci nadjeni putevi imaju ulogu u biranju novog cvora za obradu
        current_node = node_in_open_set_with_lowest_heuristic_guess(open_set, heuristic_guess)
        if current_node == target_node:
            path_found = True
            break

        # trenutni obradjen cvor izbacujemo iz skupa otvorenih cvorova. To ne znaci da je on zauvek izbacen. Moze se desiti da heursitika malo
        # zaluta ali da se onda cvor vrati u skup ako se nadje neki drugi put preko njega
        open_set.remove(current_node)
        
        for (neighbour_node, weight) in adj_list[current_node]:

            new_cheapest_path = cheapest_paths[current_node] + weight

            if new_cheapest_path < cheapest_paths[neighbour_node]:
                parents[neighbour_node] = current_node
                cheapest_paths[neighbour_node] = new_cheapest_path
                # ako smo pronasli bolji put za neki cvor od onog koji smo vec imali, moramo da pored puta azuriramo i heuristiku!
                heuristic_guess[neighbour_node] = new_cheapest_path + h(neighbour_node)
                # ako smo nasli nov najkraci put, a trenutni cvor je izbacen iz open_seta, vracamo ga nazad (zasto???)
                if neighbour_node not in open_set:
                    open_set.add(neighbour_node)

    path = []
    if path_found:
        while target_node is not None:
           path.append(target_node) 
           target_node = parents[target_node]
        path.reverse()
    
    return path


# pomocna funkcija
def node_in_open_set_with_lowest_heuristic_guess(open_set, heuristic_guess):
    result = None
    min_path = float('inf')
    for v in open_set:
        hg = heuristic_guess[v]
        if hg < min_path:
            result = v
            min_path = hg
    return result
