#include <QCoreApplication>
#include "song.h"
#include "xmlserializer.h"

#include <iostream>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString filepath = "C:/Users/Jovan/Desktop/RS/rokovi/zadaci_za_vezbanje/4.1/4_1/song.xml";

    Song s;
    XMLSerializer xmlser;

    //ne radi mi citanje iz xml lepo, ali upisivanjeizgleda radi
    xmlser.loadFromFile(s, filepath);

    std::cout << s.toString().toStdString() << std::endl;

    double newRating;
    std::cout << "Unesite novi rejting za pesmu:" << std::endl;
    std::cin >> newRating;
    std::cout << "Nov rejting unet: " << newRating << std::endl;

    s.setRating(newRating);

    std::cout << "\nUnesite putanju do fajla u koji upisujemo pesmu:" << std::endl;

    std::string newFilepath; // = "C:/Users/Jovan/Desktop/RS/rokovi/zadaci_za_vezbanje/4.1/4_1/songNew.xml";
    std::cin >> newFilepath;

    QString qFilePath{newFilepath.c_str()};

    std::cout << "Upisujem u: " << filepath.toStdString() << std::endl;
    xmlser.saveToFile(s, qFilePath);
    std::cout << "Serijalizacija zavrsena" << std::endl;

    return a.exec();
}
