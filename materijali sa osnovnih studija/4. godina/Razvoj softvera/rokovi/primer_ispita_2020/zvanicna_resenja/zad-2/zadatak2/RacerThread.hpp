#ifndef RACERTHREAD_HPP
#define RACERTHREAD_HPP

#include <QThread>

class RacerThread : public QThread
{
    Q_OBJECT
public:
    RacerThread(int i, QObject *parent = nullptr);

    void run() override;

signals:
    void updatedPosition();
    void finishedRace(int);

private:
    int m_idx;
};

#endif // RACERTHREAD_HPP
