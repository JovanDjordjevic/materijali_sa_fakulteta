#include <iostream>
#include <QMutex>
#include <QMutexLocker>

#include "MyThread.h"

using namespace std;

QMutex globalDataMutex;
extern int globalData;

void MyThread::run()
{
    for( int i=0; i<10; i++ ){
        QMutexLocker lock(&globalDataMutex);
        int x = globalData;
        cout << "Nit " << _ID << " : " << i << endl;
        x++;
        globalData = x;
    }
}
