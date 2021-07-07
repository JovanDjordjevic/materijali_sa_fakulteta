#include "workerthread.h"
#include "mainwindow.h"
#include <QMutexLocker>

WorkerThread::WorkerThread(QObject *parent, int index)
    :QThread(parent), m_index(index), m_step(200)
{
}

void WorkerThread::run()
{
    auto mainWindow = qobject_cast<MainWindow*>(parent());
    QVector<int>& vect = mainWindow->getNumbers();

    while(vect[m_index] > 0)
    {
        sleep(1);
        while(m_step > vect[m_index])
        {
            m_step /= 2;
        }

        QMutexLocker lock(&mainWindow->getMutex());
        vect[m_index] -= m_step;
        emit progressMade(m_step);
    }

}
