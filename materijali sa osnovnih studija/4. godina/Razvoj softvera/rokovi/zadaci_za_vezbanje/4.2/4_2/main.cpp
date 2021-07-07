#include <QCoreApplication>
#include <iostream>
#include "horse.h"
#include "jsonserializer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString filepath = "C:/Users/Jovan/Desktop/RS/rokovi/zadaci_za_vezbanje/4.2/4_2/horses.json";

    JSONSerializer jsonser;

    //ne radi mi citanje iz jsona
    std::cout << "Reading horses:\n";
    QVector<Horse> horses{};

    jsonser.loadFromFile(horses, filepath);
    std::cout << "Horses read:\n\n";

    std::cout << "Listing horses:\n";
    for(const auto &h : horses)
    {
        h.toString();
    }
    std::cout << "Horses Listed:\n";


    std::cout << "saving horses:\n";
    QVector<Horse> newHorses{ {"SuperHorsey", 10, 5, 1000}, {"LucyInTheSky", 20, 2, 4500},
                              {"SuperMoose", 10, 9, 1500}, {"TimTheEnchanter", 50, 40, 2000} };

    QString dest = "C:/Users/Jovan/Desktop/RS/rokovi/zadaci_za_vezbanje/4.2/4_2/horsesNew.json";
    jsonser.temp(newHorses, dest);
    std::cout << "Horses saved:\n";


    return a.exec();
}
