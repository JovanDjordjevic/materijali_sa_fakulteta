//mozda u zvanicnim materijalima ima nesto sto nikola nije pricao na vezbama

#include <iostream>
#include <string>
#include <memory>  //shared i unique pointer se nalaze u ovom zaglavlju

struct point{
    point(double x, double y) 
    {
        this->m_x = x;
        m_y = y;  
    }

    ~point()   //kao sto imamo konstruktor, mozemo napisati i nasu implementaciju za destruktor    
    {   
        //kad god se objkeat dealocira (?) poziva se njegov destruktor, ovde u nasem primeru to je na kraju maina
        //tj preciznije nakon sto se zavrsi funkcija f() jer se u nju move-ovan jedinstveni pokazivac
        //zato sto tada prestaje da postoji jedini unique_pointer koji na njega pokazuje i dealocira se memorija
        std::cout << "destruktor" <<std::endl;
    }

    std::string to_string()
    {   
        return "(" + std::to_string(m_x) + ", " + std::to_string(m_y) + ")";
    }

    double m_x;
    double m_y;
}; 

void f(std::unique_ptr<point> p){
    std::cout << "f(p): " << p->to_string() << std::endl;
}

int main(){
    //kod unique pointera ne moze da se desi da vise pokazivaca pokazuje na jedan objekat u memoriji
    //kada se taj jedan pokazivac unisti, onda se unistava i objekat
    //pravljenje ovog tipa poakzivaca je slicno kao za shared
    std::unique_ptr<point> p = std::make_unique<point>(5, -6);
    std::cout << "p: " << p->to_string() << std::endl;
    //primetimo da za unique_ptr nemamo use_count() metod jer uvek moze biti samo jedna referenca!   

    //ako pokusamo nesto tipa:   auto p2 = p;   to nece proci cak ni kompilaciju
    //primetimo da ovde ne mozemo da napravimo funkciju koja prima unique pointer kao argument zato sto ne moze da se napravi kopija za argument
    //ako bismo mogli to da uradimo to bi bilo kontradiktorno sa samom upotrebom unique pointera (ali ovakva stvar bez problema moze da se radi sa shared poitnerom)
    // (pravljenje takve funkcije bi nam izazvalo gresku u kompilaciji)
    // ipak postoji nacin da se ovo izvede pomocu std::move()
    //move radi tako sto dozvoli da se napravi novi jedinstveni pokazivac na onaj objekat u memoriji, ali pritom se brise onaj pocetni
    f(std::move(p));
    //tako da sada ovde nakon poziva funkcije f nebismo mogli da ispisujemo sadrzaj poakzivaca p
    //to ce mozda i proci kompilaciju ali se ce se program rpekinuti u izvrsavanju pogresno (?)
    //    std::cout << "p: " << p->to_string() << std::endl;+
    
    //desktruktor ce svoju poruku ispisati ovde, pre nego to se ispise "kraj"
    std::cout << "kraj" << std::endl;

    return 0;
}