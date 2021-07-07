#include <QSemaphore>
#include <iostream>
#include <vector>
using namespace std;

#include "MyThread.h"

#ifdef QT_NO_CONCURRENT
    !!! Nije podrzano !!!
#endif

int main(int argc, char **argv)
{
    Zadaci zadaci;

    int n = 10;
    vector<MyThread*> threads;

    cout << "pokretanje niti..." << endl;
    for( int i=0; i<n; i++ ){
        threads.push_back(new MyThread(i,zadaci));
        threads.back()->start();
    }

    // zadaci
    forever{
        cout << "Unesi pozitivan ceo broj: ";
        int n;
        cin >> n;
        if( n<0 )
            cout << "Greska!" << endl;
        else{
            zadaci.dodajZadatak(n);
            if( n==0 )
                break;
        }
    }

    cout << "wait..." << endl;
    forever
        if( MyThread::Finished() == n )
            break;

    cout << "end..." << endl;
    for( int i=0; i<n; i++ )
        delete threads[i];
    threads.clear();

    return 0;
}
