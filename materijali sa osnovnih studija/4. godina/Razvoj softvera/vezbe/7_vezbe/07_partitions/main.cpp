// Zadatak: Dat je vektor celih brojeva od 1 do 15.
// Transformisati vektor tako da oni brojevi koji pri deljenju brojem 3:
//   a) daju ostatak 0 idu na pocetak vektora (prva grupa),
//   b) daju ostatak 1 idu nakon prve grupe (druga grupa),
//   c) daju ostatak 2 idu nakon druge grupe (treca grupa).

#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

//funkcionali - pristup gde koristimo objekte klasa umesto funkcija
//kosrisni su npr kada zelimo da imamo nesto slicno lambdi ali da bude trajnije (?)
class DivideRemainderComparator
{   
    public:
        DivideRemainderComparator(int divider, int remainder) 
            : divider_(divider), remainder_(remainder) 
        {}

        //funkcijski objekti (a i ostali) mogu da implementiraju call operator, tj (),
        //operator se bas zove (), nije to lista parametara
        //ovo je jedini operator koji mi mozemo da implementiramo koji prima proizvlojne argumente i proizvoljnu povratnu vrednost(?)
        bool operator() (const int x) const
        {
            return x % divider_ == remainder_;
        }

    private:
        int divider_;
        int remainder_;
};


int main(int argc, char *argv[])
{
    std::vector<int> xs{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

    DivideRemainderComparator div_by_3_rem_0 {3, 0};
    //mi sada bilo gde gde bismo korisitli funkciju mozemo da koristimo ovaj funkcional
    //kada se pozove objekat kao funkcija, pozvace se zapravo operator () koji smo mi gore implementirali

    using namespace std;

    //stable aprtition prima [) interval i predikat funkciju i svi elemenit koji xzadovoljavaju predikat idu na pocetak intervala
    //kao predikat mozemo koristiti nas funkcional
    //stable partition je algoritam koji ce menjati nas vektor tako da mu ne mzoemo proslediti const iteratore
    //on takodje moze da ima povratnu vrednost (ako nam treba) a to je iterator na pocetak intervala elemenata koji ne zadovoljavaju predikat
    auto first_end = stable_partition(begin(xs), end(xs), div_by_3_rem_0);

    //funkcional mozemo i direktno konstruisati umesto da cuvamo u promenljivoj
    stable_partition(first_end, end(xs), DivideRemainderComparator{3, 1});

    //ipsis
    copy(cbegin(xs), cend(xs), ostream_iterator<int>(cout, ", "));

    return 0;
}