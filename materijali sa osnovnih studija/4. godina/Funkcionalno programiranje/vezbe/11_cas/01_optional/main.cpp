#include <iostream>
#include <string>
#include <vector>
#include <functional> //ovo nam treba za funtion (?)
#include <optional>  //u ovom zaglavlju su, od cpp17 

//neka funkcija kojoj prosledjujemo nas optional i neki predikat
//  template <typename In, typename Out>
//  std::optional<Out> transform(std::optional<In> &opt, std::funtion<Out(In)> f)

//evo jos jednog nacina da deklarisemoovu funckiju:
template <typename In, typename F>
auto transform(const std::optional<In> &opt, F f) -> std::optional<decltype(f(opt.value()))>
//ideja je bila da ne koristimo std::function nego da napravimo template koji ce da primi funkciju. Ako to uradimo moramo da napisemo i povratni tip
//ali, ako umesto auto stavimo ovo sto je iza -> dobicemo gresku jer kompajler u tom trenutku ne zna sta je f (?). Zato kao povratnu vrednost stavljamo auto, a
//imamo posebnu sintaksu -> iza koje navodimo povratnu vrednost funckije, jer u tom trenutku moze da se tumaci sta je f.
//decltype ce nam vratiti tip onoga sto se dobije kada se f primeni na opt.value, u nasem slucaju kao da pise std::optional<bool>
{   
    //ovako samo proveravamo da li optional ima vrednost, po defaultu ako je prazan bice null
    if(opt){   
        //ali ako hocemo bas da izvucemo vrednost iz optionala moramo da koristimo value()
        return f(opt.value());
    }else{
        // {} je zapravo prazan konstruktor nekog objekta (koji je to objekat zasvisi od konteksta. Ovde znamo koji je povratni tip 
        //nase funkcije tako da ce se ovde samo napraviti prazan optional)
        //ovo je preferiran pristup zbog buduceg menjanja koda. Ako promenimo povratni tip funkcije ovo ce i dalje raditi
        //mogli smo ovde i da vratimo nullopt, ali to onda radi samo za ovaj konkretan kod 
        return {};
    }
}

//evo primer neke    a -> m a    funckije, ona umotava prosledjeni argument u kontekst (kod nas kontekst optional)
std::optional<std::string> user_full_name(const std::string &login)
{
    return {"full name: " + login};
}


std::optional<std::string> to_html(const std::string &text)
{
    return {"<p>" + text + "</p>"};
}


template<typename T>
std::optional<T> join(const std::optional<std::optional<T>> &opt)
{
    if(opt)
        return opt.value();
    else
        return {};
}

//pravimo nesto sto odgovara bind uhaskelu (?)
template<typename T, typename F>
auto mbind(const std::optional<T> &opt, F f) -> decltype(f(opt.value()))
{
    if(opt){
        return f(opt.value()); 
    }
    else{
        return {};
    }
}


//definisemo i infiksni | operator koji ce da funkcionise kao u haskelu, da smo pozove nas bind
template<typename T, typename F>
auto operator| (const std::optional<T> &opt, F f)
{
    return mbind(opt, f);
}


//napravili smo operator za ispis optionala
template <typename T>
std::ostream& operator<< (std::ostream &out, const std::optional<T> value)
{
    if(value){
        out << "value: "<< *value;
    }else{
        out << "empty";
    }
    return out;
}


int main(int argc, char *argv[])
{
    //ovo je neki optional koji u sebi sadrzi ili int ili nista, kao Maybe u haskelu
    //po defaultu konstruktor optionala pravi prazan optional
    std::optional<int> i;
    //mozemo i eksplicitnmo navesti prazan optional
    std::nullopt;

    //inicijalizacija u c++ podsecanje:
    //    std::string s{};              -value initialisation
    //    std::string s("hello world"); -direktna inicijalizacija
    //    std::string s = "hello";      -copy inicijalizacija
    //    std::string s {'h', 'e', 'l', 'l', 'o'};  -list inicijalizacija
    //    ...

    //ovde smo napravili optinal u koji smo umotali broj 5
    i = std::make_optional<int>(5);

    //neka funkcija kojoj prosledjujemo nas optional i neki predikat
    auto res =  transform(i, isalnum);

    std::optional<std::string> login;
    
    //npr transformisemo login funkcijom user_full_name a onda dobijeno odatle tranformisemo funkcijom to_html
    //priemtimo da svki put kada radimo transform dobijamo optional u optionalu, pa moramo i pozvati nasu join ufnkciju da od ta dva
    //optionala napravi jedan
    std::cout << join(transform(
                        join(transform(
                            login, 
                            user_full_name
                        )),
                        to_html))
            << std::endl;           

    login = "ivan";

    //umesto join(transform()) mozemo koristiti i nas bind
    std::cout << mbind(
                        mbind(
                            login, 
                            user_full_name
                        ),
                        to_html)
            << std::endl;     


    //metodom reset() mozemo vratiti optional na praznu vrednost
    login.reset();                 

    //primer kako korsitimo onaj nas infiksni operator
    std::cout << (login | user_full_name | to_html) << std::endl;

    login = "ivan";
    std::cout << (login | user_full_name | to_html) << std::endl;
    

    return 0;
}