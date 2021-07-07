#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QSemaphore>
#include "Zadaci.h"

class MyThread : public QThread
{
Q_OBJECT
public:
    MyThread( int id, Zadaci& z )
        : _ID(id), _zadaci(z)
    {}

    static int Finished()
    {
        return _finished.available();
    }

protected:
    void run();

    int _ID;
    Zadaci& _zadaci;

    static QSemaphore _finished;
};

#endif // MYTHREAD_H
