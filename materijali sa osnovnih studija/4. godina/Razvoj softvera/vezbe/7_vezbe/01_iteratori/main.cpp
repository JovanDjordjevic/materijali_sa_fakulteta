#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main()
{   
    using namespace std;

    std::vector<int> xs;
    //vector<int> ys = {1, 2, 3};

    //vecina algoritama koje cemo videti segmente koje uzima gleda ovako: [ .. )

    //copy iz <algorithm> prima iteratore na pocetak i kraj segmenta za kopiranje iz jedne kolekcije
    //i smesta ih pocev od treceg argumenta (iterator na poziciju druge kolekcije)
    //std::copy(ys.begin(), ys.end(), xs.begin());

    //hocemo da napravimo da prva "kolekcija" za copy algoritam bude cin
    //mozemo koristiti sablonsku klasu istream_iterator<tip_koji_se_ucitava>(tok)
    //posto cin sam po sebi nema kraj, za kraj iteriranja koristi se specijalno prazan istream_iterator
    //to je objekat koji na neki nacin obavestava o kraju unosa (?), u literaturi ovakvi objekti se zovu sentineli
    std::copy(istream_iterator<int>(cin),
              istream_iterator<int>(),
              back_inserter(xs)); //xs.begin()); je ovde stajalo prvo
    //primetimo bag ovde, ako samo ovako pokrenemo program dobijamo seg fault, jer ce copy
    //u sustini da radi xs[0] = broj, xs[1]=broj ... a nas niz je deklarisan samo kao vecotr<> xs; ,a ne xs(koliko_ih_ima)
    //posto nekad ne mzoemo unapred rezervisati prostor, hocemo da nas iterator na xs radi push_back a ne xs[]=..
    //to radi back_inserter klasa
    //NOTE: istream_iterator i back_iterator su u std:: namespaceu

    //sort uzima iterator na pcoetak i kraj segmenta koji zelimo da bude sortiran (ne mora od pocetka do kraja)
    //ali, bolje je da umesto xs.begin() i xs.end() koristimo begin(xs) i end(xs) iz <itertor>
    //zatos to ako se promeni kolekcija ovo ce raditi, ali npr ako xs postane niz, prvi pristup vise nece raditi
    //jer nizovi nemaju .begin() i .end() metode
    sort(begin(xs) + 1, end(xs) - 1);    

    //mozemo copy kloristiti i za ispips, gde se kopira iz xs na cout
    //slicno kao pre, imamo ostream_iterator, on moze primiti i dodatni argument za delimiter
    //cbegin i cend su samo konstantni iteratori
    copy(cbegin(xs), cend(xs), ostream_iterator<int>(cout, ", "));
    cout<<endl;

    //niz mozemo zapravo obrnuti ali i ne moramo ako nam ne treba
    //za ispis unazad mozemo koristiti rbegin i rend iteratore
    copy(rbegin(xs), rend(xs), ostream_iterator<int>(cout, ", "));
    cout<<endl;

    return 0;
}