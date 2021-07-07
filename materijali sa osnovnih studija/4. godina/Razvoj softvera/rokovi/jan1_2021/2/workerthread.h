#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>

class WorkerThread : public QThread
{
    Q_OBJECT
public:
    WorkerThread(QObject *parent, int index);

signals:
    void progressMade(int);

    // QThread interface
protected:
    void run() override;

private:
    int m_index;
    int m_step;
};

#endif // WORKERTHREAD_H
