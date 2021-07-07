#include <iostream>
#include <string>
#include <memory>  //shared  i unique pointer se nalaze u ovom zaglavlju

struct point{
    point(double x, double y) 
    {
        this->m_x = x;
        m_y = y;  
    }

    std::string to_string()
    {   
        return "(" + std::to_string(m_x) + ", " + std::to_string(m_y) + ")";
    }

    double m_x;
    double m_y;
}; 

int main(){
    //shared pointer i unique pointer su tu da zamene obicne c-ovske pokazivace, jer oni za nas rade dealokaciju na kraju opsega
    //shared pointer kada dodje vreme za dealokaciju, proveri da li postoji jos neki shared pointer koji pokazuje na tu neku adresu
    //i ako ne postoji onda se dealocira memorija, u suprotnom se ne dealocira. Nigde sami ne radimo dealokaciju
    //shared poitnere koristimo kada zelimo da na neki objekat poakzuje vise pokazivaca, imacemo posle i unique_ptr
    //psoto je to sablonski tip, u <> stavljamo tip podataka na koji treba da pokazuje
    //pravimo ga funkcijom make_shared<tip_podatka>, a u () mozemo proslediti argumente konstruktora za nas tip u <>
    std::shared_ptr<point> p = std::make_shared<point>(5, 6);
    
    std::cout << "p " << p->to_string() << std::endl;
    //use_count() je metod deljenih pokazicvaca koji ispisuje koliko trenutno pokazuivaca pokazuje na neki objekat u memoriji
    std::cout << "# " << p.use_count() << std::endl;

    {   //mali pod-opseg
        auto p2 = p; //ovde smo napravili jos jedan pokazivac na tacku (5,6) ali primetimo da samo shared pointer p stoji na heap memoriji
                 //iako imamo dva pokazivaca sada (?)
        std::cout << "p2 " << p2->to_string() << std::endl;
        std::cout << "# " << p.use_count() << std::endl;
        std::cout << "# " << p2.use_count() << std::endl;  //nebitno je iz kog konkretnog pokazivaca pozivamo use_count()
    }  // na kraju ovog opsega p2 ce nestati i necemo vise moci da ga korsitimo
       //ALI p nece biti obrisan jer je deljeni pokazivac odradio svoju proveru i nije obrisao sadrzaj sa heapa
       //i sad mozemo da pristupimo ponovo pokazivacu p:  
    std::cout << "p " << p->to_string() << std::endl;
    std::cout << "# " << p.use_count() << std::endl;



    //p ce biti dealociran na kraju maina jer je u tom trenutku samo on taj koji pokazuje na tacku
    return 0;
}