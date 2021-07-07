// Zadatak: Napisati sablonsku funkciju count_adj_equals
// koja vraca broj uzastopnih jednakih elemenata kolekcije.

//misli se da se dva uzastopna karaktera npr aa tretiraju kao jedno ponavljanje
// npr aaa ima dva ponavljanja

#include <iostream>
#include <string>
#include <numeric>
#include <vector>


//mozemo da uradimo ovo skalarnim proizvodom, npr u nasoj niski Hooloovoo
//pomerimo nisku za jedan u levo i u pocetnoj izbacimo poslednje 'o' da bi bile jednake:
// Hooloovo | o
// ooloovoo 
//primetimo da ako imamo uzastopno pojavljivanje, u "skalarnom proizvodu" ce se "mnoziti isti karakteri"
//potrebno je da predefinisemo operacije sabiranja i mnozenja koje ce se koristiti u skalarnom
//mnozenje mozemo da stavimod a radi proveru da li su isti, vrati 0/1 dobijemo nesto oblika 01001001
//a sabiranje mozemo da stavimo da sabira jedinice dobijene mnozenjem

//svaka template kolekcija ima nacin da se iz nje izvuce informacija o tipu podataka koji ona sadrzi
//i to cemo koristiti za nase lambda funkcije
//C::value_type izvlaci tip podataka iz kolekcije C, ali onvde moramo da stavimo i typename ispred, takva je sintaksa (?)
template<typename C, typename Inner = typename C::value_type>
int count_adj_equals(const C &xs)
{   
    using namespace std;
    //inner product je skalarni proizvod
    //prva dva argumenta su iteratori na segment prve kolekcije kroz koju se iterira (nama je end -1 jer odbacujemo poslednji karakter)
    //treci arg je pocetak druge kolekcije
    //cetvrti arg je neutral za operaciju akumulacije (mi sabiramo integere tako da je neutral nama 0)
    // peti arg je opcioni, slizi za predefinisanje SABIRANJA
    // sesti arg je opcioni, slizi za predefinisanje MNOZENJA
    return inner_product(begin(xs), end(xs)-1, begin(xs)+1, 0, 
            [](const int left, const int right) { return left + right;},  //sabiranje
            [](const Inner left, const Inner right){ return left == right ? 1 : 0;});
}

int main(int argc, char *argv[])
{
    const std::string text = "Hooloovoo";

    std::cerr << text << ": " << count_adj_equals(text) << std::endl;

    const std::vector<double> numbers{-1.0, 2.36, 65.4, 65.4, 65.4, -1.0, 0.0, 5.4};

    std::cerr << "numbers : " << count_adj_equals(numbers) << std::endl;

    return 0;
}
