#include <QCoreApplication>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "cipherthread.h"

//NOTE: ovo sigurno nije dobar nacin da se radi ovaj zadatak

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::ifstream fileStream;
    fileStream.open("C:/Users/Jovan/Desktop/RS/rokovi/zadaci_za_vezbanje/5.1/5_1/lozinka.txt");

    int k;
    std::string s;
    fileStream >> k >> s;

    //std::cout << k << " " << s << std::endl;

    QVector<CipherThread*> threads;
    for(unsigned i = 0; i<s.size(); i++)
    {
        threads.append(new CipherThread(nullptr, s, i, k));
    }

    for(unsigned i = 0; i<s.size(); i++)
    {
        threads[i]->start();
    }

    std::cout << "sleeping 2 seconds" << std::endl;
    _sleep(2000);
    std::cout << "sleeping done" << std::endl;

    std::cout << s << std::endl;

    return a.exec();
}
