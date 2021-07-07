#ifndef RACERTHREAD_H
#define RACERTHREAD_H

#include <QThread>

class RacerThread : public QThread
{
    Q_OBJECT
public:
    RacerThread(QObject *parent, int index);

signals:
    void progressMade();
    void racerFinished(int index);

    // QThread interface
protected:
    void run() override;

private:
    int m_index;
};

#endif // RACERTHREAD_H
