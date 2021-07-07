#include "list.hpp"

namespace matf{

    list::list()
        : m_size(0u), m_start(nullptr)
    {}

    list::list(const list& other)
        : list() //u lisit inicijalizacija mozemo zvati i konstruktore, to nammomogucava da zovemo i konstruktor nadkklase ako treba
        //: m_size(0u), m_start(nullptr)
    {
        for (auto i =0u; i < other.m_size; i++){
            push_back(other[i]);
        }
    }

    //move konstruktor, posto radimo sa privremenim objektom (koji je &&) treba nam && arument
    list::list(list &&other)
        :m_size(other.m_size), m_start(std::move(other.m_start))
    {
        //ideja je da "ukrademo" unique pointere iz other, to smo uradili u listi inicijalizacija
        //other.m_start ce posle ovoga pokazivati na nullptr
        //za m_size ce se vrsiti kopiranje, ali to je 2 bajta pa cemo da oprostimo, tu nema bas poente koristiti std::move
        //moramo samo da pazimo, da svakako other.m_size posle ovoga moramo da dodelimo neku vrednost, jer se nece sam izmeniti (move za unique ptr hoce sam da psotavi na nullptr(?))
        other.m_size = 0u;
    }

    void list::push_back(int value)
    {
        //make_unique svoje argumente prosledjuje konstruktoru za klasu element. Posto je nullptr podrazumevano, mogli smo i da ga ne napisemo
        auto new_element = make_unique<element>(value, nullptr);
        
        //treba sad ispravno povezati pokazivace
        //kada je lista prazna m_start je nullptr, pa nam zato treba ova provera
        if(!m_start){
            //m_start = new_element;
            //linija iznad ne moze jer radimo sa unique_ptr, da bismo ga prevezali treba nam move
            m_start = std::move(new_element);
            //nadalje new_element nema vise pristup onom delu memorije, npr new_element->m_value bi izazvao segm. fault
        }
        else{
            //auto e = std::move(m_start);
            //ako napisemo kao gore, desice se neprravilno izvrsavanje, nisam bas ispratio na snimku lepo
            //nesto je bilo kao da ne zelimo u svakom koraku da krademo pokazivac nego samo da dohvatimo pokazivac na poslednji element
            //metod .get() od unique ptr vraca cist pokazivac, ali ne premesta vlasnistvo kao move
            auto e = m_start.get();
            while (e->m_next){
                //e = std::move(e->m_next);
                //linija iznad nije bila dobra iz istog razloga kao gore
                e = e->m_next.get();
            }
            e->m_next = std::move(new_element); //ovde je move okej 
        }
        m_size++;
    }

    void list::push_front(int value)
    {
        auto new_element = std::make_unique<element>(value, std::move(m_start));
        m_start = std::move(new_element);
        m_size++;
    }

    void list::pop_front()
    {
        auto old_start = std::move(m_start);
        m_start = std::move(old_start->m_next);
        m_size--;
    }

    size_t list::size() const
    {
        return m_size;
    }

    //primeti sintaksu za vracanje reference kad je funkc deo nekog namespace/klase, prvo ide & pa sve ostalo
    const int &list::operator[](size_t index) const
    {   
        //razlikujemo leve i desne vrednosti. Desna vrednost je broj/izraz koji se moze nacio sa desne strane =, npr x = 5, 5 je desna vrednost
        //leva vrednost je ono sto se nalazi sa leve strane = ali ona mora biti nesto u sta vrednnost sa desne strane moze da se upise
        //npr x = 5, x je Lvalue, to je okej, ali 5 = 6, 5 nije Lvalue
        //u c++ NE MOZEMO imati referencu na desnu vrednost!!! znaci int &x = 5 nije validno
        //npr ovde u funkciji nebi bilo validno da napipsemo samo: return 0;
        //desne vrednosti mozemo gledati kao nekakve privremene vrednosti koje sluze da se inicijalizuje ono sto je sa leve strane
        //npr: K je neka klasa,  K a = K();, tu je K() desna vrednost, ako napisemo i K b = K();, tu je opet desna vrednost, ali to nije ista vrednost (jer cim se zavrsi poziv
        //za a, K() istekne i ne moze se isti taj posle refereisati isto to K() )
        //Tip desne vrednosti u C++ je && (dupla referenca), poenta je da desnu vrednost ne mozemo da uhvatimo sa obicvnom referencom, jer nema smisla uzimati reference privremenog objekta (znaci K &c = K() nema smisla)
        // IZUZETAK od obog pravila je da mzoemo imati nesto oblika:  const K &c = K(); Time se produzava zivotni vek za K() i moci ce ponovo da se referise, ali naravno to c sad ne moze da se menja

        return at(index)->m_value;
    }
    
    //overload ove funkcije koji ce nam davati da menjamo sadrzaj, prosli nije mogao jer je cosnt funkcija koja vraca const int &
    int &list::operator[](size_t index)
    {
        return at(index)->m_value;
    }

    list &list::operator=(const list &other)
    {
        //Copy-and-swap idiom: sluzi za implementaciju exception-safe  overloada za operator dodele
        //idiom je standardni nacin kako se nesto radi
        //korak 1: kreiranje privremene kopije
        auto tmp(other); //konstuktor kopije
        //korak 2: zamena vrednosti privremene kopije i this
        std::swap(tmp.m_start, m_start);
        std::swap(tmp.m_size, m_size);
        //ovo je bezbedno za izuzetke jer ako je prosao konstruktor kopije, sigurno ce proci i korak 2 jer je std::swap funcija pravljena da bude exception safe
        return *this;
    }

    //operator dodele sa pomeranjem
    list &list::operator=(list &&other)
    {
        //Move and swap idiom: slicno kao copy and swap, samo radi pomeranje
        //Korak 1: kreiranje privremenog "ukradenog objekta"
        auto tmp = std::move(other);
        //Korak 2: zamena vrednosti privremene kopije i this
        std::swap(tmp.m_start, m_start);
        std::swap(tmp.m_size, m_size);
        return *this;
    }

    list::element *list::at(size_t index) const
    {   
        //ako je lista prazna
        if (!m_start){
            return nullptr;
        }

        auto e = m_start.get(); //ovo vrati element*
        for (auto i = 0u; i < index; i++){
            e = e->m_next.get();
            if(!e){     //ako indeks premasi velicinu liste
                return nullptr;
            }
        }   
        return e;
    }

    list::element::element(int value /*=0*/, unique_ptr<list::element> next /*=nullptr*/)
        : m_value(value), m_next(std::move(next))
    {}

}//namespace matf

std::ostream &operator<<(std::ostream &out, const matf::list &l)
{
    for(auto i = 0u; i < l.size(); i++){
        out << l[i] << " ";
    }
    return out;
}