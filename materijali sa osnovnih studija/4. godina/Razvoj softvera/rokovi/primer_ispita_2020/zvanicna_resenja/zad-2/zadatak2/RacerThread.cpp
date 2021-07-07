#include "RacerThread.hpp"

#include "MainWindow.hpp"
#include <QMutexLocker>

RacerThread::RacerThread(int i, QObject *parent)
     : QThread(parent)
     , m_idx(i)
{

}

void RacerThread::run()
{
    for (;;) {
        sleep(1);

        auto window = qobject_cast<MainWindow *>(parent());

        QMutex & mutex = window->racersMutex();
        QMutexLocker lock(&mutex); // zakljucavanje!

        auto & racers = window->racers();

        const auto speed = racers[m_idx].speed();
        const auto percent = racers[m_idx].percent();
        const auto new_percent = speed + percent;
        racers[m_idx].setPercent(new_percent);

        emit updatedPosition();

        if (new_percent >= 100) {
            break; // otkljucavanje!
        }
    } // otkljucavanje!

    emit finishedRace(m_idx);
}


















