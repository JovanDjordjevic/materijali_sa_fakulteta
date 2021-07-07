#ifndef ZADACI_H
#define ZADACI_H

#include <queue>
#include <QReadWriteLock>

class Zadaci
{
public:
    Zadaci()
    {}

    void dodajZadatak( int n )
    {
        QWriteLocker lock(&zadaciLock);
        zadaci.push( n );
    }

    int uzmiZadatak()
    {
        QWriteLocker lock(&zadaciLock);

        if( zadaci.empty() )
            return -1;

        // 0 koristimo kao oznaku za kraj,
        // ostavljamo je da bi i druge niti zavrsile sa radom
        int n = zadaci.front();
        if( n>0 )
            zadaci.pop();

        return n;
    }

private:
    QReadWriteLock  zadaciLock;
    std::queue<int> zadaci;
};

#endif // ZADACI_H
