#ifndef PITHREAD_H
#define PITHREAD_H

#include <QThread>

//bitno je da nasa klasa nasledi QThread i da ima Q_OBJECT !!

class PiThread : public QThread
{
    Q_OBJECT
public:
    PiThread(QObject *parent = nullptr);

protected:
    //nasa klasa mora da prevazidje ovaj metod iz klase QThread
    void run() override;

signals:
    //kada nit treba da vrati informacije o vise podataka, pozeljno je da se za svaki od njih napravi po signal
    //reminder: signali se samo deklarisu, a automatski se generise njihova definicija
    void progressIsMade(QString);
    void piIsCalculated(double);
};

#endif // PITHREAD_H
