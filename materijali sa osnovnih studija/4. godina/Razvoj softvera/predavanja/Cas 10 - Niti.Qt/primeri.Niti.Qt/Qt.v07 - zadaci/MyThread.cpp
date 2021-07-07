#include "MyThread.h"
#include <iostream>
#include <qglobal.h>

using namespace std;

QSemaphore MyThread::_finished;

void MyThread::run()
{
    Q_ASSERT( true );
    forever{
        int zadatak = _zadaci.uzmiZadatak();
        if( !zadatak )
            break;
        if( zadatak > 0 ){
            for( int i=1; i<=zadatak; i++ ){
                cout << "Nit " << _ID << " : " << i << endl;
                msleep(200);
            }
        }else{
            msleep(200);
        }
    }
    _finished.release();
}
