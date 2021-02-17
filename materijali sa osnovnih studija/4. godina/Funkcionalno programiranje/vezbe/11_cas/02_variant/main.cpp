#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

#include <variant>  //ubaceno od c++17
#include <cassert> 

//ovaj deo koda je pisao pri kraju vezbi, nisam bas razumeo, vezano za metod visit, ove ... prolaze kompilaciju, ne razumem sta je ovo
//rekao je da se ovo nece traziti na ispitu 
template <typename... Fs>
struct overloaded : Fs... {using Fs::operator()...; };
template <typename... Fs> overloaded(Fs...) -> overloaded<Fs...>;
//ne kapiram sta se ovde desava


//razmatramo kako mi da na neki nacin pratimo stanje neke klase, u smislu, kako da sprecimo korisnika da 
//pozove metod count() iz nase klase pre nego sto reci zapravo budu prebrojane metodom count_words
//Mozemo da postignemo ovo nekim enumom, ali ovde je pokazan nacin gde korsitimo privatne interne neke klase za oznake stanja
//imamo tri stanja, init_t kad je tek napravljeno, runnig_t dok traje prebrojavanje reci, finished_t predstavlja stanje nakon sto je 
//zavrseno prebrojavanje reci

//pitanje je samo kako da definisemo prelaz iz jednog stanja u drugo
//ovde moze da nam pomogne variant klasa. To je template klasa u kojoj mozemo navesti vise tipova koje promenljiva tog tipa moze da cuva

class program_t
{   
    private:
    //privatne klase koje predstavljaju stanja (pisali smo ih ovde na vrhu da bi bile vidljive metodu visit koji smo pisali pri dnu (?))
        class init_t{
        };

        class running_t{
            public:
                running_t(const std::string &file_name) : m_file(file_name){}

                void count_words(){
                    //neki lenj nacin da ovo ziracunamo jer je poenta zadatka rad as variantoma a ne bas ovo
                    m_count = std::distance(
                        std::istream_iterator<std::string>(m_file),
                        std::istream_iterator<std::string>()
                    );
                }

                unsigned count() const
                {
                    return m_count;
                }
            private:
                unsigned m_count = 0;
                std::ifstream m_file;
        };

        class finished_t{
            public:
                finished_t(unsigned count = 0) : m_count(count) {}

                unsigned count() const{
                    return m_count;
                }
            private:
                unsigned m_count;
        };
    //------------------------------------------------
    public:
        program_t() : m_state(init_t()) {}

        void count_words(const std::string &file_name){
            //proverimo  da li smo u init stanju. index metod mozemo koristiti da proverimo koje je stanje trenutno (init_t je 0, vidi ispod)
            //assertujemo da je neophodno da budemo u init stanju da bismo pozvali count_words
            assert(m_state.index() == 0);

            //promenimo stanje u running
            m_state = running_t(file_name);

            //prebrojavamo
            //  m_state.count_words();  nije ispravna linija koda jer je m_state variant, on samo po sebi nema count words
            //moramo nekako da uzmemo vrednosti iz varianta pa onda na to da primenimo count words
            //get<tip>() ce da vrati tip iz prosledjenog varianta
            //cratice null ako taj variant trenutno nje tipa koji smo naveli u <> tako da mzoemo i ovo koristit da proverimo koje je trenutno stanje 
            std::get<running_t>(m_state).count_words();

            //nakon prebrojavanja menjamo stanje u finished
            counting_finished();
        }

        void counting_finished(){
            const auto *state = std::get_if<running_t>(&m_state);
            assert(state != nullptr);

            m_state = finished_t( state->count() );
        }

        unsigned count() const{
            //visit je sablnska sunkfija iz standardne biblioteke. Argument joj je objekat klase koja ima definisane call operatore
            //koji se pozivajuu zavisnosti od toga sta je bio drugi argument
            //mozemo npr uraditi ovo:  std::visit(neka_klasa, m_state), gde ce neka_klasa u sebi imati predefinan call za init_t, 
            //running_t i finished_t
            //a mozemo i ovde na licu mesta definisati neku lokalnu strukturu sa tim call operatorima. Napravicemo zapravo niz lambdi 
            //tj funkcionalnih objekata (koji u pozadini imaju call operator) koji ce se pozvati u zavisnosti sta je u m_state
            return std::visit(overloaded{
                [](init_t){ return 0u; },                                   //ne zaboravi zarez na kraju
                [](const running_t &state) { return state.count(); },        //i ovde
                [](const finished_t &state) { return state.count(); }
            }, m_state);
        }
    
    private:
    //za cuvanje trenutnog stanja program_t klase koristimo variant. m_state moze biti bilo kog od ova navedena tri tipa u 
    //nekom trenutku (ali mora biti jedno od ta tri). Svakom od ovih tipova je dodeljen neki index, init_t je dobio index 0,
    //runinng_t je 1, finished_t je 2
    std::variant<init_t, running_t, finished_t> m_state;
};


int main()
{
    program_t program;
    program.count_words("main.cpp");
    
    std::cout << program.count() << std::endl;

    return 0;
}