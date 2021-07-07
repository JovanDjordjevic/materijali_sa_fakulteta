#include <iostream>
#include <QReadWriteLock>
#include <QSemaphore>
#include "MyThread.h"

using namespace std;

QReadWriteLock globalDataLock;
extern int globalData;

extern QSemaphore threadSem;

int readGlobalData()
{
    QReadLocker lock(&globalDataLock);
    return globalData;
}

void MyThread::run()
{
    for( int i=0; i<10; i++ ){
        msleep(20);
        QWriteLocker lock(&globalDataLock);
        int x = globalData;
        cout << "Nit " << _ID << " : " << i << endl;
        x++;
        globalData = x;
    }
    threadSem.release();
}
