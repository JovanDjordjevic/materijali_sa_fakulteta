# problem koji hocemo da resimo je sledeci:
# pokusavamo da kombinovanjem ascii karaktera pogodimo neki string duzine n koji smo nasumicno generisali

import string
import random

# neka nam ovo bude jedinka u generaciji
class Chromosome:
    def __init__(self, genetic_code, fitness):
        self.genetic_code = genetic_code      # ovo je neke lista slova (tj string)
        self.fitness = fitness                # neki realan broj koji ocenjuje jedinku  

    # pogledaj za sta se repr koristi
    def __repr__(self):
        return str(self)

    def __str__(self):
        return "{} = {}".format(''.join(self.genetic_code), self.fitness)


class GeneticAlgorithm:
    def __init__(self, possible_gene_values, target):
        print("Trying to guess: {}".format(''.join(target)))
        self.possible_gene_values = possible_gene_values
        self.target = target
        # ovo su parametri koje mozemo da menjamo u zavisnosti od samog problema koji resavamo
        self.max_iterations = 1000
        self.generation_size = 5000
        self.chromosome_size = len(self.target)
        self.tournament_size = 10
        self.reproduction_size = 1000                       # npr inicijalna generacija nam je 5000, a svaka naredna ce biti po 1000
        self.selection_function = self.roulette_selection   # note: ovo su funkcije, mogli smo i da odaberemo turnirsku selekciju
        self.mutation_rate = 0.1
        self.target_fitness = self.calculate_fitness(self.target) - 3

    # genetski algoritam je uglavnom uvek isti
    def optimize(self):
        population = self.initial_population()                      # generisemo neku pocetnu populaciju

        # ovo je dodato naknadno. U osnovnoj implementaciji moze da se desi da generacije stagniraju, pa smo odlucli da ako se npr ne nadje bolja jedinka
        # barem svakih 10 generacija, onda cemo da prekinemo izvrsavanje
        global_best = max(population, key=lambda x: x.fitness)
        global_best_iteration = 0
        
        for i in range(self.max_iterations):                        # imamo neki maksimalni broj generacija koje pravimo
            selected = self.selection(population)                   # iz trenutne populacije odaberemo neke jedinke (one najbolje)
            population = self.create_generation(selected)           # na osnovu njih pravimo novu generaciju
            current_best = max(population, key=lambda x: x.fitness) # biramo najbolju jedinku iz nove generacije na osnovu fitnesa
            print(current_best)

            # naknadno
            if global_best.fitness < current_best.fitness:
                global_best = current_best
                global_best_iteration = i

            if self.best_fit(current_best):                         # ako je taj najbolji fitnes bas onaj koji trazimo
                result = current_best                               # ne treba nam nista bolje pa breakujemo
                break
            
            # naknadno
            if i - global_best_iteration >= 10:
                print("No better chromosome in 10 iterations")
                result = global_best
                break
        
        return result

    # pomocna funkcija koja generise pocetnu populaciju
    def initial_population(self): 
        result = []
        for _ in range(self.generation_size):
            genetic_code = [random.choice(self.possible_gene_values) for _ in range(self.chromosome_size)]
            fitness = self.calculate_fitness(genetic_code)
            chromosome = Chromosome(genetic_code, fitness)
            result.append(chromosome)
        return result

    # fitness ce nam biti koliko se karaktera u jedinki poklapa tacno sa karakterom u targetu na toj poziciji
    def calculate_fitness(self, genetic_code):
        fitness = 0
        for i in range(self.chromosome_size):
            if genetic_code[i] == self.target[i]:
                fitness += 1
        return fitness

    # na rpedavanjima su pominjane dve selekcije:  ruletska selekcija (svaka jedinka ima sansu da bude izabrana proporcionalno njenom fitnesu)
    # i turnirska (biramo ili najbolju jedinku pa ona ide u slececu generaciju, ili biramo nekih k pa najbolja od njih ide u sledecu generaciju)
    # obratimo paznju da moze da se desi da se ovom selekcijom kako je sad napisana mozda ponavljaju jedinke
    def roulette_selection(self, population):
        # choices moze da primi ovu wights opciju koja taman radi ono sto nama treba za ruletsku selekciju
        result = random.choices(population, weights=[ x.fitness for x in population ], k = 1)
        return result[0]

    def tournament_selection(self, population):
        selected = random.sample(population, self.tournament_size)
        result = max(selected, key=lambda x : x.fitnes)
        return result

    def selection(self, population):
        result = [ self.selection_function(population) for _ in range(self.reproduction_size)]
        return result

    def create_generation(self, selected):
        result = []

        # od jednog roditelja uvek pravimo 2 dece, pa je potrebno da velicinu podelimo sa 2 da bi iz generacije u generaciju broj jedinki ostao isti
        for _ in range(self.generation_size // 2):
            parents = random.sample(selected, 2)
            child1_code, child2_code = self.crossover(parents[0], parents[1])   # kombinujemo geneteski kod roditelja

            child1_code = self.mutate(child1_code)      # da se nebi desilo da samo kloniramo roditelja, uvodimo nekakvu mutaciju u svakog childa
            child2_code = self.mutate(child2_code)

            child1 = Chromosome(child1_code, self.calculate_fitness(child1_code))
            child2 = Chromosome(child2_code, self.calculate_fitness(child2_code))

            result.append(child1)
            result.append(child2)

        return result

    def crossover(self, parent1:Chromosome, parent2:Chromosome):
        break_point = random.randint(1, self.chromosome_size)
        child1 = parent1.genetic_code[0:break_point] + parent2.genetic_code[break_point:]
        child2 = parent2.genetic_code[0:break_point] + parent1.genetic_code[break_point:]
        return child1, child2

    def mutate(self, genetic_code):
        random_value = random.random()
        if random_value < self.mutation_rate:
            radnom_index = random.randrange(len(genetic_code))
            # primetimo da ovako kako je napisano, ovde moze da se desi da mutiran gen bude isti kao i originalni, ali nama je verovatnoca da se to desi bas mala
            # pa nismo to eliminisali
            genetic_code[radnom_index] = random.choice(self.possible_gene_values)
        return genetic_code

    def best_fit(self, current_best):
        return current_best.fitness >= self.target_fitness

    


# generisemo neki nasumicni string duzine n
def get_random_string(n):
    return [random.choice(list(string.ascii_letters)) for _ in range(n) ]

if __name__ == "__main__":
    genetic_algorithm = GeneticAlgorithm(string.ascii_letters, get_random_string(100))
    result = genetic_algorithm.optimize()
    print("Best found: ", result)