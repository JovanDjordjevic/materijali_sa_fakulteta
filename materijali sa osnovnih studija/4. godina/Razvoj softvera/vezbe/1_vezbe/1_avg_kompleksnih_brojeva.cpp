#include <iostream>
#include <vector>
#include <complex>
#include <numeric> //ovde je std::accumulate

//vector, complex... su u standardnom namespaceu i treba nam std:: ispred njih
//nas namspace mozemo napraviti sa:
// namespace ime{
//     ...nase  funkcije
// }

int main(){

    std::vector<std::complex<double>> numbers;
    std::complex<double> number;

    //imamo tri vrste tokova u c++: za ulaz, za izlaz, za ulaz i izlaz
    //cin, cout, cerr su objekti, nalaze se u iostream
    // >> i << su operatori, tj funkcije koje funkcionisu kao operatori, njhigova povratna vrednost
    //je isti taj tok i zato mozemo da nanizemo: >> a >> b ...
    //complex npr definise na koji nacin se vrsi unos sa bilo kog ulaznog toka, konkretno (re, im)
    //i zbog toga mozemo direktno da ga ucitamo u promenljivu
    //kada >> naidje na EOF, on vraca tok koji nije validan tj kojis e moze konvertovati
    //u False i zato mozemo unos koristiti kao uslov

    while( std::cin >> number ){
        numbers.push_back(number);
    }

    //reference & su u sustini isto kao pokazivaci, samo sa kracim zapisom, bez * i & nadalje
    //npr int &a = b znaci da je a referenca na b, tj njena adresa, ali posle ne moramo *a da bi uzeli vrednost
    //neke vrednosti ne mogu biti referisane, o tome kasnije
    //u for each petlji mozemo staviti & da se nebi radilo implicitno kopiranje nepotrebno,
    //bez & bi se u svakom koraku tekuca vrednost iz numbers prekopirala u number

    for (std::complex<double> &number : numbers){
        std::cout << number << std::endl;
    }

    //accumulate je kao fold, uzima iteratore na pocetak kolekcije, kraj(tj nakon poslednjeg elementa)
    //i pcoetnu vrednost na koju ce redom sabirati elementi kolekcije, za kompleksne je definisano vec sabiranje
    //ako hocemo da vrsi neku dugu operaciju umesto sabiranja, mozemo proslediti opcioni cetvrti argument
    const std::complex<double> neutral = {0.0, 0.0};
    std::complex<double> mean = std::accumulate(numbers.begin(), numbers.end(), neutral);

    mean /= (double)numbers.size();

    std::cout << mean << std::endl;

    return 0;
}