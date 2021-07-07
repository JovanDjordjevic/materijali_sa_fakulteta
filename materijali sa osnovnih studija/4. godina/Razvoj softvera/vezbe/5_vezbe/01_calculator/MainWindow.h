#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "Fraction.hpp"   //dodajemo nas header

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//forward declaration za QLineEdit, da nebi imali jos jedan #include
//mi ovim kazemo kompajleru da ce ova klasa postojati negde, i time se nece zaliti kada ispod napisemo onu deklaraciju funkcije
//ali to samo zato sto mi tu klasu dole koristimo kao pokazivac (?)
class QLineEdit;

//npr forward declare nismo mogli da uradimo za nasu klasu Fraction, zato sto je ovde ne koristimo kao pokazivac, i kompajler
//ne zna sam da odredi koliko ona mesta zauzima u memoriji (a za pokazivac zna da je 4 bajta ili kolko vec)

class MainWindow : public QWidget
{
    Q_OBJECT  //ovo je makro koji se stavlja u nase klase, on ubacuje neke meta podatke bitne za prevodjenje programa
              //qt pored normalne kompilacije, ima i tzv meta-object kompilaciju (?)

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

//QT koristi pristup signal/slot. Kada se neki dogadjaj desi, salje se signal svim objketima koje taj signal moze da interesuje
//slot sluzi da obradi signal. Objekat koji treba da hvata signal, mora imati deklarisane slotove za svaki signal (?)
public slots:
    //slot za dogadjaj kad pritisnemo ++a dugme na prozoru
    void onIncA();
    void onIncB();  //++b dugme
    //mzoemo za domaci a+b i a-b, radi se sve slicno kao i ova dva

private:
    //pravimo funkciju koja ce nam procitati sadrzaj LineEdita
    Fraction parseFraction(QString fracInput) const;
    //ako samo napisemo sledecu definiciju, okruzenje ce nam se zaliti da ne zna sta je QLineEdit. Mi sad mozemo uobicajno uraditi #include <QLineEdit>
    //ali posto cemo tu klasu koristiti samo ovde (tj generalno, kada nesto korsitimo u malom broju fajlova), samo kao pokazivac (?), tj nema
    //potrebe u ovom trenutku dati celu definiciju toga sta je QLineEdit, ne zelimo #include da nam se nebi velicina izvrsnog fajla povecavala
    //ono sto cemo uraditi je Forward Declare, samo cemo gore iznad klase MainWindow, reci okruzenju da postoji neki  tamo QLineEdit
    void incrementFractionFromLineEdit(QLineEdit *le, Fraction&f);

private:
    Ui::MainWindow *ui; //automatski se generise klasa za onaj .ui sto smo pravili koja sadrzi pokazivac na njega (?)
    Fraction m_a;
    Fraction m_b;
};
#endif // MAINWINDOW_H
