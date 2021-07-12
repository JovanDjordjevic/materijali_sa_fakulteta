from queue import PriorityQueue


def dijkstra(adj_list, start_node, target_node):
    visited = set()
    D = {v : float('inf') for v in adj_list}   # najkraci putevi
    D[start_node] = 0

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
