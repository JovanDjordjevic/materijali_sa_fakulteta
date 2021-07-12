#! /usr/bin/env python
# -*- coding: utf-8 -*-

from collections import deque, defaultdict

class Graph:

    def __init__ (self, start_state, end_state):
        self.start_state = start_state
        self.end_state = end_state

    def reset_marks(self):
        self.marked = {}  

    # Heuristika
    def h(self, n):
        hamming_distance = len(self.end_state)
        ########################################################################################
        '''Studentski kod, funkcija vraca hamingovo rastojanje tekuce niske
            od ciljne niske'''
        
        for i in range(len(n)):
            if n[i] == self.end_state[i]:
                hamming_distance -=1
        ########################################################################################
        return hamming_distance


    def get_neighbors(self, state):
        neighbors = []
        ########################################################################################
        ''' Studentski kod, funkcija generise sve niske koje se razlikuju za jedan karakter
            u odnosu na prosledjenu kao argument'''

        alphabet = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
        for i in range(len(state)):
            for j in range(len(alphabet)):
                if state[i] != alphabet[j]:
                    neighbour = state[:i] + alphabet[j] + state[i+1:]
                    neighbors.append(neighbour)
        ########################################################################################
        return list(zip(neighbors, [1 for i in range(len(neighbors))]))


    def astar(self, start, stop):
        ########################################################################################
        ''' Studentski kod, kod funkcije A* prilagodjen problemu'''

        open_set = set([start])
        shortest_paths = defaultdict(lambda: float('inf'))
        shortest_paths[start] = 0
        heuristic_guess = defaultdict(lambda: float('inf'))
        heuristic_guess[start] = 0
        parents = {}
        parents[start] = None
        path_found = False

        while len(open_set) > 0:
            
            current_node = self.get_node_with_lowest_heuristic_guess(open_set, heuristic_guess)

            if current_node == stop:
                path_found = True
                break

            open_set.remove(current_node)

            for next_node, weight in self.get_neighbors(current_node):

                possible_shortest_path = shortest_paths[current_node] + weight

                if possible_shortest_path < shortest_paths[next_node]:
                    shortest_paths[next_node] = possible_shortest_path
                    parents[next_node] = current_node
                    heuristic_guess[next_node] = possible_shortest_path + self.h(next_node)
                    if next_node not in open_set:
                        open_set.add(next_node)
                
        # rekonstrukcija puta
        result = []
        if path_found:
            node = stop
            while node is not None:
                result.append(node)
                node = parents[node]
            result.reverse()

        return result
        ########################################################################################

    ########################################################################################
    def get_node_with_lowest_heuristic_guess(self, open_set, heuristic_guess):
        min_hg = float('inf')
        result = None
        for elem in open_set:
            hg = heuristic_guess[elem]
            if hg < min_hg:
                min_hg = hg
                result = elem
        return result
    ########################################################################################

def main():
    start_state = 'SECRET'
    end_state = 'PORUKA'

    game = Graph(start_state, end_state)
    print(game.astar(start_state, end_state))

if __name__ == "__main__":
    main()

