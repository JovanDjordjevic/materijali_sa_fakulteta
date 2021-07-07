#ifndef ITEMTHREAD_H
#define ITEMTHREAD_H

#include <QThread>

class ItemThread : public QThread
{
    Q_OBJECT
public:
    ItemThread(QObject *parent, int row, int col, int signalStrength);

signals:
    void progressMade();

    // QThread interface
protected:
    void run() override;

private:
    int m_row;
    int m_col;
    int m_signalStrength;
};

#endif // ITEMTHREAD_H
