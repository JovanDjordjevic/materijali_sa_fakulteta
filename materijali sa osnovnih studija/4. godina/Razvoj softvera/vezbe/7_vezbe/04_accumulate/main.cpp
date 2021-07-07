//dat vektor celih brojeva od 1 do 5
//napraviti nisku od neparnih brojeva tog vektora
#include <iostream>
#include <vector>
#include <numeric>  //accumulate je u ovom zaglavlju, a vecina ostalih je u <algorithm>
#include <iterator>
#include <string>

using namespace std;

std::string append(const std::string &acc, const int x)
{   
    if( x % 2 != 0){
        return acc + std::to_string(x);
    }
    return acc;
}

int main()
{
    const std::vector<int> xs{1, 2, 3, 4, 5};  //  -> "135"

    //prva dva arg su [) interval, treci je neutral (za nas prazna niska)
    //i opcioni cetvrti argument je funkcija. Mi ovde moramo funkciju jer su u xs integeri a neutral je string i accumulate ne moze sam to
    const auto result = std::accumulate(cbegin(xs), cend(xs), string{}, append);
    cout << result << endl;

    return 0;
}