//zadatak: napisati sablonksu funckiju count_adj_equals koja
//vraca bron uzastopnih jednakih elemenata kolekcija

#include <iostream>
#include <string>
#include <numeric>
#include <vector>

template <typename T>
int count_adj_equals(const T &xs)
{   
    //imamo nesto kao skalarni proizvod
    //[1,2,3] [3,4,5] = (1 op 3) op1 (2 op 4) op1 (3 op 5)
    return std::inner_product (
        std::cbegin(xs), std::cend(xs)-1,                       //pcoetak i kraj prve kolekcije
        std::cbegin(xs)+1,                                      //pocetak druge
        0,                                                      //akumulator
        [](const auto &x, const auto &y) {return x + y;},       //op1
        [](const auto &x, const auto &y) {return x == y ? 1 : 0;} //op 
    );
}

//lambda funckije su u pozadini funkcionalni objekti, ono sto stavimo u () su zapravo parametri call oepratora, a 
//ono sto stavimo u [] ce biti polja klase

//evo npr primer i kako bismo sa inner product proverili da li je funkcija sortirana
template <typename T>
int is_sorted(const T &xs)
{   
    return std::inner_product (
        std::cbegin(xs), std::cend(xs)-1,                 
        std::cbegin(xs)+1,                                      
        true,                                                      
        [](const bool &x, const bool &y) {return x && y;},      
        [](const auto &x, const auto &y) {return x <= y ? 1 : 0;} 
    );
}

int main(int argc, char *argv[])
{
    const std::string text = "Hiooloovoo";
    std::cerr << text << ": " << count_adj_equals(text) << std::endl;

    const std::vector<double> numbers {-1.0, 2.56, 44.3 , 3.3 ,3.3, 3.3};
    std::cerr << "numbers: " << count_adj_equals(numbers) << std::endl;

    return 0;
}
