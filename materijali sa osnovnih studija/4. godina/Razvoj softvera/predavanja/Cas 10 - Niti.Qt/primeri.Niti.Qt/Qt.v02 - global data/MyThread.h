#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class MyThread : public QThread
{
Q_OBJECT
public:
    MyThread( int id )
        : _ID(id)
    {}

protected:
    void run();
    int _ID;
};

#endif // MYTHREAD_H
