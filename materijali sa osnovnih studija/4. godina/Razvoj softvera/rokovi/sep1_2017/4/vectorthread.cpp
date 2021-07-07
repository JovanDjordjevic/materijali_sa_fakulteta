#include "vectorthread.h"
#include <QFile>
#include <qmath.h>

VectorThread::VectorThread(QObject *parent,QString &filepath)
    : QThread(parent), m_filepath(filepath)
{

}

void VectorThread::run()
{
    QFile file(m_filepath);
    if(!file.open(QFile::ReadOnly)) {
        return;
    }

    double res = 0.0;

    auto numbers = file.readLine().split(' ');
    for(auto n : numbers)
    {
        res += n.toDouble() * n.toDouble();
    }

    res = sqrt(res);

    emit calculationFinished(res);
}
