#include "MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    //automatski ce biti generisane ove linije ispod
    QApplication a(argc, argv);   //pokrece aplikaciju
    MainWindow w;     //instanca naseg prozora
    w.show();         //metod koji prikaze prozor
    return a.exec();  //a.exec ce pozvati beskonacnu petlju dogadjaja (event loop), koja proverava da li se dogadjaj desio
                      //za razliku od  obicnog c++ programa, ovo ce se prekinuti tek kada mi sami zatvorimo prozor, a ne akda sve operacije budu izvrsene
}
