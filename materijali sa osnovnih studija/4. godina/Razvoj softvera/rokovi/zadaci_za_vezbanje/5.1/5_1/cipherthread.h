#ifndef CIPHERTHREAD_H
#define CIPHERTHREAD_H

#include <QThread>

class CipherThread : public QThread
{
    Q_OBJECT

public:
    CipherThread(QObject *parent, std::string &s, int pos, int k);

    // QThread interface
protected:
    void run() override;

private:
    std::string &m_s;
    int m_pos;
    int m_k;
};

#endif // CIPHERTHREAD_H
