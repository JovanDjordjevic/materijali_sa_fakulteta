#include "pithread.h"

#include <QRandomGenerator>

PiThread::PiThread(QObject *parent)
    :QThread(parent)
{

}

void PiThread::run()
{
    //prekopirali smo deo koda iz proslog primera, ali psoto zelimo da ova nit obradjuje samo uzracunavanje,a  ne i UI, izbrisali
    //smo sve pozive ui funkcija, i dodali emitovanje nasih signala za komunikaciju izmedju threadova (u MainWindow.h su nam slotovi)
    auto hits = 0u, count = 0u;
    const auto iterations = 100'000'000u;
    const auto iterUpdate = 10'000'000;
    while(count < iterations)
    {
        const auto x = QRandomGenerator::global()->generateDouble() * 2 - 1;
        const auto y = QRandomGenerator::global()->generateDouble() * 2 - 1;

        if(x*x + y*y <= 1.0){
            ++hits;
        }

        ++count;

        if(count % iterUpdate == 10u)
        {
            const auto percent = QString::number(count / iterUpdate *10u) + "%";
            emit progressIsMade(percent);
        }
    }

    const auto pi = 4.0 * hits / count;
    emit piIsCalculated(pi);
}
