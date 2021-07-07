#ifndef MATF_LIST_HPP
#define MATF_LIST_HPP

#include<memory>
#include<iostream>

using namespace std;

//u primeru se trazi da napravimo klasu list u namespaceu matf na osnovu nekog datog uml dijagrama
namespace matf{
    class list{
    public:
        list();
        list(const list& other); //konstruktor kopije
        list(list &&other); //move konstruktor, od c++17 imamo move-sematic
        //primena je npr sledece. Ako imamo  funkciju f koja u sebi pravi listu  x i onda radi return x, desice se da ako u mainu
        //napisemo y = f(), f ce napraviti objekat liste na svom stek okviru i kada se zavrsi f taj stek okvir ce nestati (samim tim logicno je
        //da ce se desiti kopiranje vrednosti iz x u y). Move semantiko izbegavamo to kopiranje (jer je copy skup)
        void push_back(int value);
        void push_front(int value);
        void pop_front();
        size_t size() const;
        //[] su takodje operator, npr list[3], primetimo da  nismo imali vracanje referecnce
        //return naredba bi radila kopiranje, sto nije problem za int, ali jeste za komplikovane tipove
        const int &operator[](size_t index) const;  //ovaj const nam nece dati da vrsimo izmene liste sa []
        //mzoemo imati i overload koji nam omogucuje da menjamo sadrzaj 
        int &operator[](size_t index);
        //operator dodele, vracamo list & da bismo mogli da imamo nesto oblika: l1 = l2 = l3 kao u C-u
        list &operator=(const list &other);
        //kaos to mozemo imati konstruktor pomeranja, mozemo imati i operator dodele koji pomera
        list &operator=(list &&other);
    private:
        //na uml dijagramu se vidi da nam treba klasa element koju cemo koristiti samo u klasi lista
        //tako da ima smisla definisati je kao unutrasnju klasu klase list(tj ovde smo stavili da to
        //bude struktura jer je u uml ionako sve javno, svejedno je)
        struct element{  
            explicit element(int value = 0, unique_ptr<element> next = nullptr); //podrazumevani konstruktor
            int m_value;
            unique_ptr<element> m_next;
        };

        element *at(size_t index) const;

    private:
        size_t m_size;
        unique_ptr<element> m_start;
    };

} //kaja od namespace matf

std::ostream &operator<<(std::ostream &out, const matf::list &l);

#endif //MATF_LIST_HPP