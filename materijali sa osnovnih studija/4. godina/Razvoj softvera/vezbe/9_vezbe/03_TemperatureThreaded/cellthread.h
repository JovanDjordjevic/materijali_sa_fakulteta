#ifndef CELLTHREAD_H
#define CELLTHREAD_H

#include <QThread>

class CellThread : public QThread
{
    Q_OBJECT
public:
    //jedna nit ce biti zaduzena za menjanje vrednosti jedne celije iz tabele, ali ona mora da dobije i informacije o okolnim
    //celijama zbog nacina na koji treba da se uradi zadatak. Prosledicemo indekse i,j polja koje menjamo i treba na neki nacin da dobijemo i Room
    //mozemo na dva nacina, jedan je da prosledimo &Room kao argument (da nema kopiranja) a drugi je da stavimo da parent ove klase
    //bude bas MainWindow a onda odatle da pozovemo metod getRoom()
    CellThread(const int i, const int j, QObject *parent = nullptr);

protected:
    void run() override;

signals:
    //da imamo informaciju koja tacno nit je zavrsila sa radom
    void threadFinished(int i, int j);

private:
    int _i;
    int _j;

};

#endif // CELLTHREAD_H
