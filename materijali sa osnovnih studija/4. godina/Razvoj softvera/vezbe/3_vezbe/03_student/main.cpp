#include <iostream>
#include <vector>

//ovako se pravi enum u c++. Korisno je kada unapred imamo neki konacni skroz poznati domen kom podaci 
//mogu da pripadaju, npr za nas smer studenta
enum class Studies{
    Mathematics,
    Informatics,
    AstronomyAndAstrophysics
};

class student{
public:
    student(const std::string &name, const Studies &studies)
        :m_name(name), m_studies(studies)   //vektor m_grades ce biti podrazumevano inicijalizovan za nas
    {}

    // Destruktori baznih klasa UVEK moraju da budu deklarisani kao virtualni,
    // da bi se pozivali ispravni destruktori tokom unistavanja.
    virtual ~student()
    {
        std::cout << "~student" << std::endl;
    }

    //ako je metod virtual, to znaci da ce neka podklasa da ga overriduje (pritom se u podklasi mora pisati override)
    //metod moze biti apstraktan, tj da nema telo i to se pise kao ime_metoda(args...) = 0; To =0 je oznaka kompilatoru da je apstraktan
    //u hijerarhiji na svakom putu od apstraktne klase do listovaa u nekom trenutku se mora implementirati apstraktni metod
    //posto se svakako mora overridovati, uglavnom se i apstraktni metodi oznacvavaju sa virtual
    virtual std::string name() const
    {
        return m_name + " (" + program() + ") ";
    }

protected:
    std::string program() const
    {
        switch (m_studies)
        {
        case Studies::Mathematics:
            return "Matematika";
        case Studies::Informatics:
            return "Informatika";
        case Studies::AstronomyAndAstrophysics:
            return "A&A";
        default:
            throw "Nepoznat Smer";
        }
    }

private:
    std::string m_name;
    Studies m_studies;
    std::vector<unsigned> m_grades;
};

//nasledjivanje u c++, po defaultu nasledjivanje je private, tj svi public metodi nadklase ce u podklasi biti private (?)
//to ne zelimo i 99% slucajeva, tako da korsitimo public nasledjivanje, tj ono sto je bilo public u nadklasi, bice public i u potkalsi
//U svakom slucaju ono sto je u nadklasi bilo privatno, svakako ne mozemo direktno da koristimo iz podklase (treba nam neki geter)
class master_student : public student{
public:
    master_student(const std::string &ime, const Studies &studies, const std::string &thesis, const std::string &mentor)
        //u listi inicijalizacija pozivamo konstruktor nadklase sa odgovarajucim argumentima
        :student(ime, studies), m_thesis(thesis), m_mentor(mentor)
    {}

     ~master_student()
    {
        std::cout << "~master_student" << std::endl;
    }

    //prevazilazimo metod iz nadklase (koji je morao da bude oznacen sa virtual)
    std::string name() const override
    {   
        //public/protected metod iz nadklase mozemo pozvati ovako:
        return "MSC " + student::name() ;
    }

private:
    std::string m_thesis;
    std::string m_mentor;
};



int main(){

    //vrednost iz enuma se prosledjuje sa ime_enuma::vrednost
    student s1("Petar Petrovic", Studies::Mathematics);
    std::cout << s1.name() << std::endl;

    master_student s2("Janko Jankovic", Studies::Informatics, "Plan 9 FS","Mirko Mirkovic");
    std::cout << s2.name() << std::endl;

    //ako imamo studenta s1 i master studenta s2 i pokusamo da napsiemo nesto ovako:  student s3 = s2; docice do "slicinga"
    //tj kompilator ce da zanemari sve iz s2 sto se ne nalazi vec u s1, tj tretirace master studenta kao obicnog studenta, ignorisace sva dodatna polja i metode
    //tj desice se da ako imamo vector<student> {s1, s2, s3} svima ce se npr name() ispisivati kao za obinog studenta (npr u Javi se ovo ne desava, nego se pozivaju odgovarajuci metodi)
    //rresenje za ovo u c++ je da se cuvaju pokazivaci na objekte (tada ce se zapravo pozivati pravi metodi iz podklase):
    std::vector<student *> studs = {&s1, &s2};
    for(const auto &s : studs)
    {   
        //posto je s sad pokazivac, moramo sa ->
        std::cout << s->name() << std::endl;
    }


    //vidi ostatak primera u materijalima, nije ga zavrsio na vezbama

    return 0;
}