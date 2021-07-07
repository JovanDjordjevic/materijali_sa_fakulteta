#include <iostream>
#include <string>
#include <vector>

// kljucna rec new alocira objkeat na hipu
// int *p;
// p = new int(10);
// *p je pokazivac na int, tj njegova adresa, a pristup vrednosti koja se nalazi na adresi p radimo dereferenciranjem: 
// npr cout << *p; 
// sve sto se alocira mora se na kraju i dealocrati sa delete:
// delete p
// uglavnom zelimo da posle delete eksplicitno navedemo da pokazivac ne pokazuje ninasta, da bi nam pukao program ako
// pokusamo da ga korsitimo ponovo:
// p = nullptr;  //NULL je iz C, u C++ imamo specijalno nullptr
// ako hocemo da alociramo npr niz od 5 intova:
// int *p = new int[5];
// za nizove napravljene sa new[] specijalno imamo delete[]: delete[] p; Za nizove obican delete brise samo pokazivac na niz ali 
// ne radi dealokaciju za svaki pojedinacni elelment, dok je delete[] kao for petlja gde dealocira svaki element

//u c++ struct i class su prakticno ista stvar, samo sto je u strukturi podrazumevano sve public
struct point{
    point(double x, double y)  //konstruktor
    {
        this->m_x = x;   //immao this samo sto je to ovde pokazivac pa mora ->
        m_y = y;         //ali mozemo i bez this, ali samo u situacijama da nam se polja sturkture NE zovu isto kao parametri konstruktora
        // y = y;  //oov se kompilira ali nece dati ispravan rezultat
    }

    std::string to_string()
    {   
        //ova to_string(m_x) je funkcija iz zaglavlja string, ne ova nasa funkcija koju pisemo
        // mi ovde pisemo overload za to_string, da nismo ovako uradili, obican to_string nebi mogao sam da zakljuci kako da ispise tacku 
        return "(" + std::to_string(m_x) + ", " + std::to_string(m_y) + ")";
    }

    double m_x;
    double m_y;
};  //na kraju strukture/klase mora ;

int main(){
    point a(3, 4);   //alokacija objeta na STEKU
    point b = point(-2, 1); //pre c++17 ovaj nacin inicijalizacije je bio sporiji nego onaj iznad, zato sto se prvo
                            //pravila neka tacka a onda kopirala u promenljivu b, ali od c++17 oba nacina su ista
    point *c = new point(5,7); //ako radimo sa new, ono sto dobijemo je pokazivac!!! takodje, ovo alocira na hipu a ne na steku funkcije main()
    point d{3, -4};  //mozemo i viticastim zagradama, isto je

    point e[] = { {1,2}, {3,4}, {5,6} };  //niz na STEKU
    point *f = new point[]{ {1,2}, {3,4}, {5,6} }; //mozemo pojedinacno inicijalizovati elemente niza sa {}
    //nema nikakvog razloga da pisemo ovo kao u liniji iznad zato sto na raspolaganju imamo std::vector 
    std::vector<point> g = { {1,2}, {3,4}, {5,6} };
    // std::vector<point> f { {1,2}, {3,4}, {5,6} }; moze i bez =
    //rad sa vektorima je bolji jer imamo vec gotove metode za rad sa njima i nemamo potrebu da sami petljamo sa memorijom i alokacijom/dealokacijom itd
    //takodje vektor ce za nas uraditi dealokaciju

    std::cout << a.m_x << " " << a.m_y << std::endl;
    std::cout << a.to_string() << std::endl;

    //primetimo da ovde imamo curenje memorije zato sto nismo brisali nase pokazivace, to smo uradili za primer

    return 0;
}