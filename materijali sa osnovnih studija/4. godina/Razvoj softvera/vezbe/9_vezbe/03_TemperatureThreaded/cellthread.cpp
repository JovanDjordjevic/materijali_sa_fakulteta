#include "cellthread.h"
#include "mainwindow.h"
#include "room.h"


CellThread::CellThread(const int i, const int j, QObject *parent)
    :QThread(parent), _i(i), _j(j)
{

}

void CellThread::run()
{
    //parent() metod nekog objekta vraca QObject* na parenta, ali posto mi znamo da je taj aprent MainWindow, mozemo da ga kastujemo
    //takodje, dobra praksa je da za ova kastovanja ne koristimo cast iz c++ nego bas ovaj qobject_cast<>()
    MainWindow *window = qobject_cast<MainWindow*>(parent());
    //linija ispod nebi radila da nismo imali cast
    auto &room = window->getRoom();

    //sinhronizacija, vidi objasnjenje u MainWindow::starThreads() funkciji
    QMutexLocker lock(&window->getRoomMutex());

    auto tempDiff = 0.0;

    tempDiff += room.getTemperatureDiffFromCellAbove(_i, _j);
    tempDiff += room.getTemperatureDiffFromCellBelow(_i, _j);
    tempDiff += room.getTemperatureDiffFromCellLeft(_i, _j);
    tempDiff += room.getTemperatureDiffFromCellRight(_i, _j);

    room.updateNewTemperatureForCell(_i, _j, tempDiff);

    emit threadFinished(_i, _j);
}
