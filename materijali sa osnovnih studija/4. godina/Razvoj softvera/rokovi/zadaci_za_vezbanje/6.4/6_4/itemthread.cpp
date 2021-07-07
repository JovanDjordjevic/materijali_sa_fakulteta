#include "itemthread.h"
#include "mainwindow.h"
#include "map.h"
#include <QMutexLocker>

ItemThread::ItemThread(QObject *parent, int row, int col, int signalStrength)
    :QThread(parent), m_row(row), m_col(col), m_signalStrength(signalStrength)
{

}

void ItemThread::run()
{

    auto mainWindow = qobject_cast<MainWindow*>(parent());

    while(m_signalStrength > 0)
    {
        sleep(2);
        m_signalStrength--;

        QMutexLocker locker(&mainWindow->getMutex());
        //.....

    }


}
