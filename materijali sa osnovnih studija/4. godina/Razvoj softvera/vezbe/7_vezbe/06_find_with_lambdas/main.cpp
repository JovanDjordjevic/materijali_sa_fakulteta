#include <vector>
#include <algorithm>
#include <iostream>
#include <functional> //ovde je bind()

class Value
{
    public:
        Value(const int value) : value(value) {}

        bool odd() const
        {
            return value % 2 == 1;
        }

        bool even() const
        {
            return value % 2 == 0;
        }

        bool between(const int min, const int max) const
        {
            return value >= min && value <= max;
        }
    
        const int value;
};


bool f(Value v){
    return v.even();
}


int main(){
    using namespace std;

    //primetimo da ovakva inicijalizacija radi zato sto se konstruktor poziva implicitno
    //da smo u klasi gore naveli explicit nebi radilo
    vector<Value> values {1,2,3,4,5};

    //treci arg je predikat, tj funkcija koja prima jedan(?) argument i vraca bool vrednost
    //vraca iterator na prvi element u prosledjenom intervalu koju zadovoljava prosledjeni predikat (samo 1 element)
    //npr da smo hteli poslednji element mogli smo crbegin i crend
    const auto iter1 = find_if(cbegin(values), cend(values), f);
    //cout << iter1->value << endl;

    //prosli pristup mozemo da skratimo tako sto korismo lambda funkciju
    //sintaksa je [](lista argumenata){ telo funkcije }
    const auto iter2 = find_if(cbegin(values), cend(values), 
                       [](const Value &v){
                            return v.even();
                       });
    cout << iter2->value << endl;

    //hocemo da nadjemo npr prvi element veci od nekog limita
    //lambda funkcije mozemo sacuvati i u promenljivu
    const auto limit = 3;
    //u starijim standardima npr c++11, ako neku promenljivu deklarisanu van lambda funkcije koristimo u telu
    //funkcije, moramo da je "vezemo", to radimo tako sto koristimo [] deo lambda funkcije i u njega samo navedemo promenljive koje se vezuju
    //npr u c++17... ovo ne mora da se radi
    //ako samo stavimo [limit] vrednost ce se kopirati, ali mozemo i da stavimo & da izbegnemo kopiranje
    //mozemo i npr staviti [l = 3] i onda l koristiti u telu (primetimo da ovde ne navodimo tip niti auto, on sam dedukuje)
    const auto lambda1 = [&limit](const Value &v){
                            return v.value > limit;
                        };
    const auto iter3 = find_if(cbegin(values), cend(values), lambda1);
    cout << iter3->value << endl;

    //NOTE: bind je pokazao samo za primer, ne koristi se vise posle c++11 jer sad imamo labda funkc
    //bind sluzi za kreiranje parcijalne aplikacije, kao ono iz haskela
    //prvi argument je referenca neke funkcije nizeg reda
    //2 i 4 kao fiksiramo da budu min i max iz funkcije between, a nase vrednosti koji ne mzoemo da vezemo
    //prosledimo specijalnim znakom _1, _2, _3 itd (ti_n su iz std::placehodlers::... ima do _29)
    using namespace std::placeholders;
    auto between_2_4 = std::bind(&Value::between, _1, 2, 4); 

    const auto iter4 = find_if(cbegin(values), cend(values), between_2_4);
    cout <<iter4->value << endl;

    return 0;
}