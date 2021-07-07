#include <iostream>
#include <QMutex>

#include "MyThread.h"

using namespace std;

QMutex globalDataMutex;
extern int globalData;

void MyThread::run()
{
    for( int i=0; i<1000; i++ ){
        globalDataMutex.lock();
        int x = globalData;
        cout << "Nit " << _ID << " : " << i << endl;
        x++;
        globalData = x;
        globalDataMutex.unlock();
    }
}
