//ovo nije za ispiti

#include <iostream>

using namespace std;

class X{};

void g(X &x){}
void g(X &&x){}

//  T && se zove univerzalna referenca
// T = X -> f(X &&x)
// T = X& -> f(X& &&x) -> f(X &x)
// T = X&& -> f(X&& &&x) -> f(X &&x)
//poenta je ako ovo funkciji prosledimo objekat po elvoj referenci uhvatice je po levoj
//a ako prosledimo po desnoj uhvatice je po desnoj
//dakle imamo jednu funkciju koja se ponasa na dva razlicita nacina, po potrebi
//to se zove savrseno nasledjivanje
//ovo je posebno korisno kada treba da imamo funkciju koja vise argumenata moze da primi po levoj ili desnoj referenci
//jer onda pisemo 1 funkc umesto 4,9,16.. 2^n overloadova...
template<typename T>
void f(T &&x){

    //forward gleda da li je x uhvacen po levoj/desnoj referenci i onda to x prosledi
    //funkciji g kao levu/desnu referencu , tj zadrzi ono stanje koje je imao kada je primljen (?)
    g(std::forward<T>(x)));
    cout << ""<<endl;
}

int main(){

    return 0;
}