#include <iostream>
#include <QReadWriteLock>
#include "MyThread.h"

using namespace std;

QReadWriteLock globalDataLock;
extern int globalData;

int readGlobalData()
{
    QReadLocker lock(&globalDataLock);
    return globalData;
}

void MyThread::run()
{
    for( int i=0; i<100; i++ ){
        msleep(20);
        QWriteLocker lock(&globalDataLock);
        int x = globalData;
        //cout << "Nit " << _ID << " : " << i << endl;
        x++;
        globalData = x;
    }
}
