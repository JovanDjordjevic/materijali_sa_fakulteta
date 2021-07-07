#include "racerthread.h"
#include "mainwindow.h"
#include <QMutexLocker>
#include <QDebug>
#include "racer.h"

RacerThread::RacerThread(QObject *parent, int index)
    :QThread(parent), m_index(index)
{

}

void RacerThread::run()
{
    auto mainWindow = qobject_cast<MainWindow*>(parent());

    while(1){
        sleep(1);
        //qDebug() << "started" << QThread::currentThreadId();

        QMutexLocker locker(&mainWindow->getMutex());
        QVector<Racer>& racers = mainWindow->getRacers();

        racers[m_index].m_percentage += racers[m_index].m_speed;
        emit progressMade();

        if(racers[m_index].m_percentage >= 100)
        {
            emit racerFinished(m_index);
            break;
        }

    }

}
